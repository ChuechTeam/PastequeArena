#ifndef PASTEQUEARENA_MAINMENUSCENE_H
#define PASTEQUEARENA_MAINMENUSCENE_H

#include "Engine.h"

namespace PastequeArena {

    class MainMenuScene : public Scene {
    public:
        static std::unique_ptr<MainMenuScene> Create(Engine& engine);

    protected:
        explicit MainMenuScene(Engine& engine) : Scene(engine) {}
    };

} // PastequeArena

#endif //PASTEQUEARENA_MAINMENUSCENE_H
