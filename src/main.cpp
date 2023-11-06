#include <raylib-cpp.hpp>
#include "Engine.h"
#include "MainMenuScene.h"
#include <raygui.h>
#include "FrameData.h"
#include <iostream>
using namespace PastequeArena;

int main() {
    Engine engine;

    raylib::Font guiFont = engine.GetAssetLoader().LoadFont("RussoOne-Regular.ttf", 20);
    GuiSetFont(guiFont);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    PastequeArena::FrameData fd{
        .image = "pouet",
        .worldScale = 0.15f,
        .frames = {
                PastequeArena::FrameData::Frame {
                    .textureRect = { 0, 0, 100, 100 },
                    .pivot = { 50, 100 },
                    .colliders = {
                            PastequeArena::FrameData::Collider {
                                .origin = { 0, 0 },
                                .extent = { 100, 100 },
                                .isHitBox = true,
                                .isHurtBox = false
                            }
                    }
                }
        }
    };
    fd.WriteToStream(std::cout);

    engine.AddScene(MainMenuScene::Create(engine));

    engine.GameLoop();

    return 0;
}
