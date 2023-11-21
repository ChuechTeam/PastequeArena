#ifndef PASTEQUEARENA_VEC_H
#define PASTEQUEARENA_VEC_H

#include "Real.h"

namespace PastequeArena::Math {
    template<typename T = real>
    struct Vec2 {
        T x;
        T y;

        Vec2() = default;
        Vec2(T x, T y) : x(x), y(y) {}
        ~Vec2() = default;

        // All operators (+, -, /, *)
        Vec2 operator+ (Vec2 b) {
            return Vec2(x + b.x, y + b.y);
        }

        Vec2 operator- (Vec2 b) {
            return Vec2(x - b.x, y - b.y);
        }

        // Dot product
        Vec2 operator* (Vec2 b) {
            return Vec2(x * b.x, y * b.y);
        }

        Vec2 operator/ (Vec2 b) {
            return Vec2(x / b.x, y / b.y);
        }

        // Assignment operators (+=, -=, /=, *=)
        Vec2& operator+= (Vec2 b) {
            x += b.x;
            y += b.y;
            return *this;
        }

        Vec2& operator-= (Vec2 b) {
            x -= b.x;
            y -= b.y;
            return *this;
        }

        Vec2& operator*= (Vec2 b) {
            x *= b.x;
            y *= b.y;
            return *this;
        }

        Vec2& operator/= (Vec2 b) {
            x /= b.x;
            y /= b.y;
            return *this;
        }

        real Norm() {
            return Sqrt(x * x + y * y);
        }
    };

    template <typename T>
    inline Vec2<T> operator*(T scalar, Vec2<T> vec) {
        return Vec2<T>(scalar * vec.x, scalar * vec.y);
    }

    template <typename T>
    inline Vec2<T> operator/(Vec2<T> vec, T scalar) {
        return Vec2<T>(vec.x / scalar, vec.y / scalar);
    }
}

namespace PastequeArena {
    using Vec2 = Math::Vec2<>;
}

#endif //PASTEQUEARENA_VEC_H
