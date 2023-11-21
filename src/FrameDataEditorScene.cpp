#include "FrameDataEditorScene.h"
#include "FrameData.h"
#include "raygui.h"

using namespace PastequeArena;
using PixelVec = FrameData::PixelVec;

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

        if (spriteTexture.IsReady()) {
            RVector2 size = spriteTexture.GetSize();
            spriteTexture.Draw((screen - size) / 2);
        }

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

        char zoomStr[16];
        std::snprintf(zoomStr, 15, "%.2f", view.zoom);
        GuiSlider(Rectangle{76, screen.y - 80, 128, 32}, "Zoom", zoomStr, &view.zoom, 0.5f, 4.0f);



        // Tool state management

        if (toolState == ToolState::Idle) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CursorWithinTexture(GetCursorPos())) {
                toolState = ToolState::AddingBox;
                toolData.addingBox.startTex = CursorToTexture(GetCursorPos());
            }
        } else if (toolState == ToolState::AddingBox) {
            PixelVec cur{GetMouseX(), GetMouseY()};
            PixelVec start = TextureToCursor(toolData.addingBox.startTex);
            if (start.x > cur.x) { // width would be negative
                std::swap(start.x, cur.x);
            }
            if (start.y > cur.y) { // height would be negative
                std::swap(start.y, cur.y);
            }
            DrawRectangle(start.x, start.y, std::abs(cur.x - start.x), std::abs(cur.y - start.y),
                          Fade(GREEN, 0.5f));

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                toolState = ToolState::Idle;
            }
        }
    }

    void CreateFrameData() {
        frameData = FrameData{
                .image = chosen.string(),
                .worldScale = 1.0f,
                .frames = {
                }
        };
    }

    PixelVec CursorToTexture(PixelVec cursor) {
        RVector2 screenF{engine.GetWindow().GetSize()};

        PixelVec screen{(int) screenF.x, (int) screenF.y};
        PixelVec texSize{spriteTexture.width, spriteTexture.height};

        // screen_pos = tex_pos + (screen - size) / 2
        // ==> tex_pos = screen_pos - (screen - size) / 2

        PixelVec v = cursor - ((screen - texSize) / 2);
        v.x = Math::Clamp(v.x, 0, texSize.x - 1);
        v.y = Math::Clamp(v.y, 0, texSize.y - 1);

        return v;
    }

    PixelVec TextureToCursor(PixelVec texturePos) {
        RVector2 screenF{engine.GetWindow().GetSize()};

        PixelVec screen{(int) screenF.x, (int) screenF.y};
        PixelVec texSize{spriteTexture.width, spriteTexture.height};

        return texturePos + ((screen - texSize) / 2);
    }

    bool CursorWithinTexture(PixelVec cursorPos) {
        PixelVec UpLeft = TextureToCursor({0, 0});
        PixelVec BottomRight = TextureToCursor({spriteTexture.width, spriteTexture.height});

        return cursorPos.x >= UpLeft.x && cursorPos.x <= BottomRight.x
               && cursorPos.y >= UpLeft.y && cursorPos.y <= BottomRight.y;
    }

    static PixelVec GetCursorPos() {
        return {GetMouseX(), GetMouseY()};
    }

    std::vector<std::filesystem::path> options;
    std::string optionsStr;
    std::filesystem::path chosen;
    int chosenIdx = 0;

    RTexture spriteTexture;
    FrameData frameData;

    struct View {
        float zoom;
    } view;

    enum class Mode : uint8_t {
        Selection,
        CreateFrame,
        AddCollider
    } mode;

    enum class ToolState : uint8_t {
        Idle,
        AddingBox,
        MovingVertex,
        MovingBox,
        MovingPivot
    } toolState = ToolState::Idle;
    union {
        struct AddingBox {
            PixelVec startTex;
        } addingBox;
    } toolData;


    bool bShowDropdown = false;
};

std::unique_ptr<FrameDataEditorScene> FrameDataEditorScene::Create(Engine& engine) {
    return std::make_unique<ActualFrameDataEditorScene>(engine);
}
