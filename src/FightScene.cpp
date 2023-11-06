#include "FightScene.h"
#include "raygui.h"
#include <array>
#include <unordered_map>
#include "Fight.h"

using namespace PastequeArena;

RVector2 ToFloat(FixedVector2 vec) {
    const RVector2& ve = RVector2{static_cast<float>(vec.x), static_cast<float>(vec.y)};
    return ve;
}

class ActualFightScene final : public FightScene {
public:
    explicit ActualFightScene(Engine& engine) : FightScene(engine) {}

    void Init() override {
        fight.InitializeFighters();
    }

    void Update() override {
        float deltaTime = GetFrameTime();
        timeAcc += deltaTime;

        FightInputButtons fpInput = FightInputButtons::None;
        fpInput = fpInput | (IsKeyDown(KEY_LEFT) ? FightInputButtons::Left : FightInputButtons::None);
        fpInput = fpInput | (IsKeyDown(KEY_RIGHT) ? FightInputButtons::Right : FightInputButtons::None);

        std::array<FightInput, 2> inputs{};
        inputs[0].buttons = fpInput;

        while (timeAcc >= FightDt) {
            timeAcc -= FightDt;
            fight.AdvanceNextFrame(inputs);
        }

        if (IsKeyDown(KEY_LEFT)) {
            fight.state.fighters[0].position.x -= FixedInt{1.5f * deltaTime};
        }
        if (IsKeyDown(KEY_RIGHT)) {
            fight.state.fighters[0].position.x += FixedInt{1.5f * deltaTime};
        }

        if (IsKeyPressed(KEY_D)) {
            drawDebug = !drawDebug;
        }
    }

    void Draw() override {
        float wantedWidth = 10.0;
        // wanted_width = screen_width / zoom
        float zoom = (float) GetScreenWidth() / wantedWidth;
        float effectiveHeight = (float) GetScreenHeight() / zoom;

        Camera2D camera{
                RVector2{(float) GetScreenWidth(), (float) GetScreenHeight()} / 2,
                RVector2{0, effectiveHeight * -0.15f},
                0.0,
                zoom};
        BeginMode2D(camera);

        // Draw the ground
        DrawLineEx(Vector2{-100, 0.03f}, Vector2{100, 0.03f}, 0.05f, GRAY);

        // Draw the fighters
        for (auto& fighter: fight.state.fighters) {
            if (!textures.contains(fighter.move)) {
                std::array<RTexture, 4>& outTextures = textures[fighter.move];
                fighter.move->CreateTextures(engine, outTextures);
            }
            Sprite sprite = fighter.move->MakeFighterSprite(engine, fighter, textures[fighter.move]);

            RVector2 spritePos = ToFloat(fighter.position) - sprite.pivot;

            // Flip the sprite
            if (fighter.facing == FacingDirection::Left) {
                sprite.sourceRect.width = -sprite.sourceRect.width;
            }

            sprite.texture.Draw(sprite.sourceRect, RRectangle{spritePos, sprite.worldSize});
        }

        // Draw debug stuff
        if (drawDebug) {
            for (auto& fighter: fight.state.fighters) {
                FighterCollider& collider = fight.sim.colliders[fighter.id];

                for (uint32_t i = 0; i < collider.numBoxes; i++) {
                    FighterCollider::Box& box = collider.boxes[i];
                    auto rect = FixedRectangle::CenteredUpwards(box.origin, box.size);

                    RVector2 pos = ToFloat(fighter.position + rect.Position());
                    RVector2 size = ToFloat(rect.Size());

                    DrawRectangleLinesEx(
                            RRectangle{pos, size},
                            0.01f,
                            box.isHitBox ? RED : box.isHurtBox ? BLUE : GREEN);
                }
            }
        }

        EndMode2D();
    }

    Fight fight;
    float timeAcc = 0.0f;
    bool drawDebug = false;

    std::unordered_map<FighterMove *, std::array<RTexture, 4>> textures;
};

std::unique_ptr<FightScene> FightScene::Create(Engine& engine) {
    return std::make_unique<ActualFightScene>(engine);
}