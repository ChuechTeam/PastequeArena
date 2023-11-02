#include "FightScene.h"
#include "raygui.h"

using namespace PastequeArena;

class ActualFightScene final : public FightScene {
public:
    explicit ActualFightScene(Engine& engine) : FightScene(engine) {}

    void Draw() override {
        static const char *text = "Bagarre !";

        Font font = GuiGetFont();
        auto fontSize = static_cast<float>(font.baseSize);
        RVector2 size = MeasureTextEx(font, text, fontSize, 1);
        RVector2 screen{static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
        ::DrawTextEx(font, text, (screen - size) / 2, fontSize, 1, BLACK);
    }
};

std::unique_ptr<FightScene> FightScene::Create(Engine& engine) {
    return std::make_unique<ActualFightScene>(engine);
}