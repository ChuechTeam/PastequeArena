#include "FrameDataEditorScene.h"
#include "FrameData.h"
#include "raygui.h"

using namespace PastequeArena;
using PixelVec = FrameData::PixelVec;

constexpr float MoveSpeed = 500.0f;

class ActualFrameDataEditorScene : public FrameDataEditorScene {
public:
    explicit ActualFrameDataEditorScene(Engine& engine) : FrameDataEditorScene(engine) {}

    void Init() override {
        auto path = engine.GetAssetLoader().GetAssetRootPath();
        for (const std::filesystem::path& file: std::filesystem::recursive_directory_iterator(path)) {
            if (file.extension().string() == ".png") {
                options.push_back(file);
            }
        }

        size_t rootLength = engine.GetAssetLoader().GetAssetRootPath().string().length() + 1;
        for (const std::filesystem::path& option: options) {
            optionsStr += option.string().substr(rootLength) + ";";
        }
        if (!optionsStr.empty()) {
            optionsStr.pop_back();
        }
    }

    void Draw() override {
        RVector2 screen{engine.GetWindow().GetSize()};
        view.halfScreen = screen / 2;

        // Movement and zoom
        if (IsKeyDown(KEY_LEFT)) {
            view.target.x -= GetFrameTime() * MoveSpeed / view.zoom;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            view.target.x += GetFrameTime() * MoveSpeed / view.zoom;
        }
        if (IsKeyDown(KEY_UP)) {
            view.target.y -= GetFrameTime() * MoveSpeed / view.zoom;
        }
        if (IsKeyDown(KEY_DOWN)) {
            view.target.y += GetFrameTime() * MoveSpeed / view.zoom;
        }
        view.zoom += GetMouseWheelMove() * 0.1f;

        Camera2D camera{view.halfScreen, view.target, 0, view.zoom};

        BeginMode2D(camera);

        if (spriteTexture.IsReady()) {
            DrawRectangle(0, 0, spriteTexture.width, spriteTexture.height, Fade(PURPLE, 0.15f));
            spriteTexture.Draw(0, 0);
            DrawRectangleLinesEx(RRectangle{-1, -1, (float)(spriteTexture.width + 1), (float)(spriteTexture.height + 1)},
                                 2.0f, BLACK);
        }

        EndMode2D();

        int selectedOption = chosenIdx;
        if (GuiDropdownBox(Rectangle{8, 8, 400, 32}, optionsStr.c_str(), &selectedOption, bShowDropdown)) {
            if (bShowDropdown) {
                chosen = options[selectedOption];
                chosenIdx = selectedOption;
                spriteTexture = engine.GetAssetLoader().LoadTexture(chosen.string().c_str());
                CreateFrameData();
            }
            bShowDropdown = !bShowDropdown;
        }

        char posTxt[32];
        std::snprintf(posTxt, 32, "(%.2f, %.2f)", view.target.x, view.target.y);
        GuiLabel(Rectangle{screen.x - 128, 0, 128, 32}, posTxt);

        // Modes
        {
            constexpr float ButtonWidth = 150;
            constexpr float ButtonSpacing = 10;
            float startY = screen.y - 80;
            float startX = screen.x / 2 - ((ButtonWidth * 3 + ButtonSpacing * (3 - 1)) / 2);

            bool selectMode = (mode == Mode::Selection);
            GuiToggle(Rectangle{startX, startY, ButtonWidth, 32}, "Selection", &selectMode);

            bool createFrameMode = (mode == Mode::CreateFrame);
            GuiToggle(Rectangle{startX + ButtonWidth + ButtonSpacing, startY, ButtonWidth, 32}, "Create Frame",
                      &createFrameMode);

            bool addColliderMode = (mode == Mode::AddCollider);
            GuiToggle(Rectangle{startX + (ButtonWidth + ButtonSpacing) * 2, startY, ButtonWidth, 32}, "Add Collider",
                      &addColliderMode);

            if (selectMode && mode != Mode::Selection) {
                mode = Mode::Selection;
            } else if (createFrameMode && mode != Mode::CreateFrame) {
                mode = Mode::CreateFrame;
            } else if (addColliderMode && mode != Mode::AddCollider) {
                mode = Mode::AddCollider;
            }
        }

        // Zoom
        char zoomStr[16];
        std::snprintf(zoomStr, 15, "%.2f", view.zoom);
        GuiSlider(Rectangle{76, screen.y - 80, 128, 32}, "Zoom", zoomStr, &view.zoom, 0.5f, 4.0f);


        // Frame info
        {
            constexpr float XOff = 300;
            constexpr float XMargin = 10;
            constexpr float InnerXOff = XOff - XMargin;
            constexpr float Width = 250;
            constexpr float Height = 300;
            constexpr float InnerWidth = 250 - 2 * XMargin;

            float yOff = 348;
            GuiGroupBox(Rectangle{screen.x - XOff, screen.y - yOff, Width, Height}, "Frame Info");
            yOff -= 10;
            GuiButton(Rectangle{screen.x - InnerXOff, screen.y - yOff, 32, 32}, "<");

            char frameNumStr[16];
            std::snprintf(frameNumStr, 15, "%d/%d", 0, 0);
            Vector2 textSize = MeasureTextEx(GuiGetFont(), frameNumStr,
                                             (float) GuiGetStyle(DEFAULT, TEXT_SIZE),
                                             (float) GuiGetStyle(DEFAULT, TEXT_SPACING));
            GuiLabel(Rectangle{screen.x - InnerXOff + (InnerWidth - textSize.x) / 2,
                               screen.y - yOff - (textSize.y - 32) / 2, textSize.x, textSize.y},
                     frameNumStr);


            GuiButton(Rectangle{screen.x - InnerXOff + InnerWidth - 32, screen.y - yOff, 32, 32}, ">");
        }

        // Tool state management

        if (toolState == ToolState::Idle) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CursorWithinTexture(GetCursorPos())) {
                toolState = ToolState::AddingBox;
                toolData.addingBox.startTex = ViewToTexture(GetCursorPos());
            } else if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
                toolState = ToolState::MovingView;
                toolData.movingBox.prevCursorPos = GetCursorPos();

                SetMouseCursor(MOUSE_CURSOR_RESIZE_ALL);
            }
        } else if (toolState == ToolState::AddingBox) {
            RVector2 cur{GetCursorPos()};
            RVector2 start = TextureToView(toolData.addingBox.startTex);
            if (start.x > cur.x) { // width would be negative
                std::swap(start.x, cur.x);
            }
            if (start.y > cur.y) { // height would be negative
                std::swap(start.y, cur.y);
            }
            DrawRectangleV({start.x, start.y}, {std::abs(cur.x - start.x), std::abs(cur.y - start.y)},
                           Fade(GREEN, 0.5f));

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                toolState = ToolState::Idle;
            }
        } else if (toolState == ToolState::MovingView) {
            RVector2 currentCursorPos = GetCursorPos();
            RVector2 deltaPos = currentCursorPos - toolData.movingBox.prevCursorPos;
            view.target -= deltaPos / view.zoom;
            toolData.movingBox.prevCursorPos = currentCursorPos;
            if (IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE)) {
                toolState = ToolState::Idle;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
    }

private:

    void CreateFrameData() {
        frameData = FrameData{
                .image = chosen.string(),
                .worldScale = 1.0f,
                .frames = {
                }
        };
    }

    PixelVec ViewToTexture(RVector2 viewPos) const {
        RVector2 texSize = spriteTexture.GetSize();

        RVector2 v = (viewPos - view.halfScreen) / view.zoom + view.target;
        v.x = Math::Clamp(v.x, 0.0f, texSize.x - 1);
        v.y = Math::Clamp(v.y, 0.0f, texSize.y - 1);

        return {(int) std::round(v.x), (int) std::round(v.y)};
    }

    RVector2 TextureToView(PixelVec texturePos) const {
        return (RVector2{(float) texturePos.x, (float) texturePos.y} - view.target) * view.zoom + view.halfScreen;
    }

    bool CursorWithinTexture(RVector2 cursorPos) {
        RVector2 UpLeft = TextureToView({0, 0});
        RVector2 BottomRight = TextureToView({spriteTexture.width, spriteTexture.height});

        return cursorPos.x >= UpLeft.x && cursorPos.x <= BottomRight.x
               && cursorPos.y >= UpLeft.y && cursorPos.y <= BottomRight.y;
    }

    static RVector2 GetCursorPos() {
        return RVector2{(float) GetMouseX(), (float) GetMouseY()};
    }

    std::vector<std::filesystem::path> options;
    std::string optionsStr;
    std::filesystem::path chosen;
    int chosenIdx = 0;

    RTexture spriteTexture;
    FrameData frameData;

    struct View {
        // Cache-y variables
        RVector2 halfScreen;

        RVector2 target{0, 0};
        float zoom = 1.0f;
    } view;

    enum class Mode : uint8_t {
        Selection,
        CreateFrame,
        AddCollider
    } mode;

    enum class ToolState : uint8_t {
        Idle,
        MovingView,
        AddingBox,
        MovingVertex,
        MovingBox,
        MovingPivot
    } toolState = ToolState::Idle;
    union {
        struct AddingBox {
            PixelVec startTex;
        } addingBox;
        struct MovingBox {
            Vector2 prevCursorPos;
        } movingBox;
    } toolData;


    bool bShowDropdown = false;
};

std::unique_ptr<FrameDataEditorScene> FrameDataEditorScene::Create(Engine& engine) {
    return std::make_unique<ActualFrameDataEditorScene>(engine);
}
