#include <raylib-cpp.hpp>
#include "Engine.h"
#include "MainMenuScene.h"
#include <raygui.h>

using namespace PastequeArena;

int main() {
    Engine engine;

    raylib::Font guiFont = engine.GetAssetLoader().LoadFont("RussoOne-Regular.ttf", 20);
    GuiSetFont(guiFont);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    engine.AddScene(MainMenuScene::Create(engine));

    engine.GameLoop();

    return 0;
}
