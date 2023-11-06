#include "Fight.h"
#include "Moves/IdleMove.h"

using namespace PastequeArena;

void Fight::InitializeFighters() {
    // Initialize their id and default move
    for (int i = 0; i < state.fighters.size(); i++) {
        state.fighters[i].id = i;
        state.fighters[i].move = &Moves::Idle;
        Moves::Idle.Init(*this, state.fighters[i]);
    }

    state.fighters[0].position = FixedVector2{-1.0, 0.0};
    state.fighters[1].position = FixedVector2{1.0, 0.0};
    state.fighters[1].facing = FacingDirection::Left;
}

void Fight::AdvanceNextFrame(const std::array<FightInput, 2>& fighterInputs) {
    state.time++;

    for (Fighter& fighter : state.fighters) {
        FighterCollider collider = fighter.move->Update(*this, fighter);

        // Mirror the colliders origin if the fighter is facing left.
        if (fighter.facing == FacingDirection::Left) {
            for (uint32_t i = 0; i < collider.numBoxes; i++) {
                collider.boxes[i].origin.x = -collider.boxes[i].origin.x;
            }
        }

        sim.colliders[fighter.id] = collider;
    }
}
