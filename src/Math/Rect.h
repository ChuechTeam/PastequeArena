#ifndef PASTEQUEARENA_RECT_H
#define PASTEQUEARENA_RECT_H

#include "Vec.h"

namespace PastequeArena::Math {
    template <typename T = real>
    struct Rect {
        Vec2<T> origin;
        Vec2<T> extent;

        Rect() : origin(), extent() {}
        Rect(Vec2<T> origin, Vec2<T> extent) : origin(origin), extent(extent) {}
        Rect(T x, T y, T width, T height) : origin(x, y), extent(width, height) {}

        bool Contains(Vec2<T> point) {
            return point.x >= origin.x && point.x <= origin.x + extent.x
                && point.y >= origin.y && point.y <= origin.y + extent.y;
        }
    };
}

namespace PastequeArena {
    using Math::Rect;
}

#endif //PASTEQUEARENA_RECT_H
