#include "FrameDataEditorScene.h"
#include "raygui.h"

using namespace PastequeArena;

class ActualFrameDataEditorScene : public FrameDataEditorScene {
public:
    explicit ActualFrameDataEditorScene(Engine& engine) : FrameDataEditorScene(engine) {}

    void Init() override {
        auto path = engine.GetAssetLoader().GetAssetRootPath();
        for (const std::filesystem::path& file : std::filesystem::recursive_directory_iterator(path)) {
            if (file.extension().string() == ".png") {
                options.push_back(file);
            }
        }

        size_t rootLength = engine.GetAssetLoader().GetAssetRootPath().string().length() + 1;
        for (const std::filesystem::path& option : options) {
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
            }
            bShowDropdown = !bShowDropdown;
        }
    }

    std::vector<std::filesystem::path> options;
    std::string optionsStr;
    std::filesystem::path chosen;
    int chosenIdx = 0;

    RTexture spriteTexture;

    bool bShowDropdown = false;
};

std::unique_ptr<FrameDataEditorScene> FrameDataEditorScene::Create(Engine& engine) {
    return std::make_unique<ActualFrameDataEditorScene>(engine);
}
