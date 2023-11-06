#ifndef PASTEQUEARENA_FIGHT_H
#define PASTEQUEARENA_FIGHT_H

/*
 * Contains the core game logic for the fight.
 */

#include "Engine.h"
#include "FixedInt.h"
#include <array>

namespace PastequeArena {
    constexpr size_t MoveDataSize = 64;
    constexpr float FightDt = 1.0f / 60.0f;

    using MoveId = uint16_t;
    using FighterId = uint8_t;

    enum class FacingDirection : uint8_t {
        Left,
        Right
    };

    // TODO: MULTIPLAYER - Should be moved
    struct Sprite {
        RTexture const& texture;
        RRectangle sourceRect; // In texture-space
        RVector2 worldSize;
        RVector2 pivot; // In sprite-space, bounded by worldSize
    };

    struct FighterCollider {
        struct Box {
            FixedVector2 origin; // Displacement from the fighter's position
            FixedVector2 size; // Size of the box, growing upwards from the origin, horizontally centered.
            bool isHitBox = false;
            bool isHurtBox = false;
        };

        std::array<Box, 6> boxes;
        uint32_t numBoxes = 0;
    };

    class FighterMove {
    public:
        virtual ~FighterMove() = default;

        virtual MoveId GetMoveId() { return 0; } // TODO!

        virtual void Init(class Fight& fight, struct Fighter& fighter) {}

        virtual FighterCollider Update(class Fight& fight, struct Fighter& fighter) {
            return FighterCollider{};
        }

        // TODO: MULTIPLAYER - Should be moved
        virtual void CreateTextures(Engine& engine, std::array<RTexture, 4>& outTextures) = 0;

        virtual Sprite MakeFighterSprite(Engine& engine, Fighter const& fighter, std::array<RTexture, 4>& textures) = 0;

        template <typename T>
        T& GetData(Fighter& fighter);
    };

    struct Fighter {
        FighterId id = 0;
        FacingDirection facing = FacingDirection::Right;
        int16_t health = 10000;
        int16_t maxHealth = 10000;

        // The position vector uses fixed points integers.
        // We could use floats, but we could have determinism issues between the server
        // and the client (different machines processing floating points differently).
        FixedVector2 position{0, 0};

        // The current state of the fighter.
        FighterMove *move = nullptr;
        std::array<uint8_t, MoveDataSize> moveData{};
    };

    enum FightInputButtons : uint8_t {
        None = 0,
        Left = 1 << 1,
        Right = 1 << 2,
        Up = 1 << 3,
        Down = 1 << 4,
    };

    inline FightInputButtons operator|(FightInputButtons a, FightInputButtons b) {
        return static_cast<FightInputButtons>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
    }

    struct FightInput {
        FightInputButtons buttons;
    };

    class Fight {
    public:
        // The core data of the fight. Can be stored and reloaded to load snapshots of the game.
        struct State {
            std::array<Fighter, 2> fighters;
            uint32_t time = 0; // Frames elapsed
        } state;

        // Transitory data that is used during the simulation.
        struct Simulation {
            std::array<FighterCollider, 2> colliders;
        } sim;

        void InitializeFighters();
        void AdvanceNextFrame(std::array<FightInput, 2> const& fighterInputs);
    };

    template <typename T>
    T& FighterMove::GetData(Fighter& fighter) {
        static_assert(sizeof(T) <= sizeof(MoveDataSize), "The data struct is too large.");
        return *reinterpret_cast<T*>(fighter.moveData.data());
    }

} // PastequeArena

#endif //PASTEQUEARENA_FIGHT_H
