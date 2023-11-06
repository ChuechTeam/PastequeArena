#include "IdleMove.h"

using namespace PastequeArena;
using namespace PastequeArena::Moves;

void IdleMove::CreateTextures(Engine& engine, std::array<RTexture, 4>& outTextures) {
    outTextures[0] = engine.GetAssetLoader().LoadTexture("nori_idle01.png");
}

Sprite IdleMove::MakeFighterSprite(Engine& engine, const Fighter& fighter, std::array<RTexture, 4>& textures) {
    return Sprite(textures[0], RRectangle{0, 0, 341, 341}, RVector2{2, 2}, RVector2{1, 2});
}

FighterCollider IdleMove::Update(Fight& fight, Fighter& fighter) {
    constexpr int BodyWidth = 136;
    constexpr int BodyHeight = 178;

    return FighterCollider{
            .boxes = {
                    // Body
                    FighterCollider::Box{
                            .origin = FixedVector2{-0.075, 0.0},
                            .size   = FixedVector2{BodyWidth / (341.0f / 2.0f), BodyHeight / (341.0f / 2.0f)},
                            .isHitBox = true,
                            .isHurtBox = false
                    }
            },
            .numBoxes = 1,
    };
}
