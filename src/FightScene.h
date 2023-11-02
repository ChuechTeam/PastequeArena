#ifndef PASTEQUEARENA_FIGHTSCENE_H
#define PASTEQUEARENA_FIGHTSCENE_H

#include "Engine.h"

namespace PastequeArena {

    class FightScene : public Scene {
    public:
        static std::unique_ptr<FightScene> Create(Engine& engine);

    protected:
        explicit FightScene(Engine& engine) : Scene(engine) {}
    };

} // PastequeArena

#endif //PASTEQUEARENA_FIGHTSCENE_H
