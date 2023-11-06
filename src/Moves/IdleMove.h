#ifndef PASTEQUEARENA_IDLEMOVE_H
#define PASTEQUEARENA_IDLEMOVE_H

#include "Fight.h"

namespace PastequeArena::Moves {

    inline class IdleMove : public FighterMove {
    public:
        FighterCollider Update(class PastequeArena::Fight &fight, struct PastequeArena::Fighter &fighter) override;

        void CreateTextures(Engine& engine, std::array<RTexture, 4>& outTextures) override;

        Sprite MakeFighterSprite(Engine& engine, const Fighter& fighter, std::array<RTexture, 4>& textures) override;
    } Idle{};

} // PastequeArena

#endif //PASTEQUEARENA_IDLEMOVE_H
