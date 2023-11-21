#ifndef PASTEQUEARENA_RAYLIBCONVERSIONS_H
#define PASTEQUEARENA_RAYLIBCONVERSIONS_H

#include "Vec.h"
#include "raylib-cpp.hpp"

namespace PastequeArena::Math {
    RVector2 ToRVector2(Vec2<> vec) {
        return RVector2(vec.x, vec.y);
    }
}

#endif //PASTEQUEARENA_RAYLIBCONVERSIONS_H
