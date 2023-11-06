#include "MainMenuScene.h"
#include "FightScene.h"
#include "FrameDataEditorScene.h"
#include <raygui.h>

/*
 * Scenes are split into two parts. For a scene S, we have:
 *    - the public class S
 *    - the private class ActualS
 *
 * That might seem like an unnecessary complication, but it greatly improves compile time.
 * If we had decided to put the entire class in the header, each field/function addition
 * would trigger a large recompilation: each file that reference this scene would be rebuilt!
 *
 * Instead, each time you add a function or a field to the scene, the only file that needs
 * to be recompiled is the Scene's cpp file. Much better for iteration time.
 *
 * The scene can be created using the S::Create() method, which creates a new instance
 * of the ActualS class.
 */

using namespace PastequeArena;

class ActualMainMenuScene final : public MainMenuScene {
public:
    explicit ActualMainMenuScene(Engine& engine) : MainMenuScene(engine) {
        font = engine.GetAssetLoader().LoadFont("RussoOne-regular.ttf", 48);
    }

    void Draw() override {
        RVector2 titleSize = MeasureTextEx(font, "Pasteque ARENA", 48, 1);
        RVector2 screen{static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
        RVector2 boxSize{titleSize.x, 125};

        font.DrawText("Pasteque ARENA", Vector2{(screen.x - titleSize.x) / 2, (screen.y - boxSize.y) / 2}, 48, 1,
                      BLACK);

        RVector2 buttonSize{boxSize.x, 50};
        RVector2 buttonPos{(screen.x - buttonSize.x) / 2, (screen.y + boxSize.y) / 2 - buttonSize.y};
        if (GuiButton(raylib::Rectangle(buttonPos, buttonSize), "Play")) {
            engine.AddScene(FightScene::Create(engine));
            engine.UnloadScene(*this);
            return;
        }

        const RVector2 button2Size{250, 40};
        if (GuiButton(raylib::Rectangle{(screen.x - button2Size.x)/2, screen.y - button2Size.y - 8,
                                        button2Size.x, button2Size.y}, "Frame data editor")) {
            engine.AddScene(FrameDataEditorScene::Create(engine));
            engine.UnloadScene(*this);
            return;
        }
    }

    raylib::Font font;
};

std::unique_ptr<MainMenuScene> MainMenuScene::Create(Engine& engine) {
    return std::make_unique<ActualMainMenuScene>(engine);
}
