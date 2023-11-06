#ifndef PASTEQUEARENA_FIXEDINT_H
#define PASTEQUEARENA_FIXEDINT_H

#include <cstdint>

// A signed 32-bit integer with a fixed decimal precision of 4 digits.
// MAX = INT32_MAX / 10000 = 214748.3647
// MIN = INT32_MIN / 10000 = -214748.3648
struct FixedInt {
    static constexpr int precision = 10000;

    int32_t raw = 0;

    FixedInt() = default;

private: // Make this private so no incidents happen with conversions
    explicit FixedInt(int32_t raw) : raw(raw) {}

public:
    explicit FixedInt(float f) : raw(static_cast<int32_t>(f * precision)) {}

    static FixedInt Raw(int32_t raw) {
        return FixedInt(raw);
    }

    static FixedInt FromInt(int32_t val) {
        return FixedInt(val * precision);
    }

    [[nodiscard]] float ToFloat() const {
        return static_cast<float>(raw) / precision;
    }

    explicit operator float() const {
        return ToFloat();
    }
};

inline FixedInt operator+(FixedInt a, FixedInt other) {
    return FixedInt::Raw(a.raw + other.raw);
}

inline FixedInt operator-(FixedInt a, FixedInt other) {
    return FixedInt::Raw(a.raw - other.raw);
}

inline FixedInt operator*(FixedInt a, FixedInt other) {
    // M = (p*n)*(p*m) = p*p*(n*m)
    // M / p = p*(n*m)
    return FixedInt::Raw((a.raw * other.raw) / FixedInt::precision);
}

inline FixedInt operator/(FixedInt a, FixedInt other) {
    // (p * p * n)/(p * m) = p*(n/m)
    return FixedInt::Raw((a.raw * FixedInt::precision) / other.raw);
}

inline FixedInt operator+=(FixedInt& a, FixedInt other) {
    a = a + other;
    return a;
}

inline FixedInt operator-=(FixedInt& a, FixedInt other) {
    a = a - other;
    return a;
}

inline FixedInt operator*=(FixedInt& a, FixedInt other) {
    a = a * other;
    return a;
}

inline FixedInt operator/=(FixedInt& a, FixedInt other) {
    a = a / other;
    return a;
}

inline FixedInt operator-(FixedInt a) {
    return FixedInt::Raw(-a.raw);
}

struct FixedVector2 {
    FixedInt x;
    FixedInt y;

    FixedVector2() = default;

    FixedVector2(FixedInt x, FixedInt y) : x(x), y(y) {}

    FixedVector2(float x, float y) : x(x), y(y) {}
};

inline FixedVector2 operator+(FixedVector2 a, FixedVector2 other) {
    return FixedVector2{a.x + other.x, a.y + other.y};
}

inline FixedVector2 operator-(FixedVector2 a, FixedVector2 other) {
    return FixedVector2{a.x - other.x, a.y - other.y};
}

inline FixedVector2 operator*(FixedInt other, FixedVector2 v) {
    return FixedVector2{v.x * other, v.y * other};
}

inline FixedVector2 operator/(FixedVector2 v, FixedInt other) {
    return FixedVector2{v.x / other, v.y / other};
}

struct FixedRectangle {
    FixedInt x;
    FixedInt y;
    FixedInt width;
    FixedInt height;

    FixedRectangle() = default;

    FixedRectangle(FixedInt x, FixedInt y, FixedInt width, FixedInt height) : x(x), y(y), width(width),
                                                                              height(height) {}

    FixedRectangle(FixedVector2 position, FixedVector2 size) : x(position.x), y(position.y), width(size.x),
                                                               height(size.y) {}


    static FixedRectangle CenteredUpwards(FixedVector2 position, FixedVector2 size) {
        FixedVector2 recPos = position - FixedVector2{size.x / FixedInt(2.0f), size.y};
        return {recPos, size};
    }

    [[nodiscard]] FixedVector2 Size() const { return {width, height}; }
    [[nodiscard]] FixedVector2 Position() const { return {x, y}; }
};

#endif //PASTEQUEARENA_FIXEDINT_H
