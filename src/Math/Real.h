#ifndef PASTEQUEARENA_REAL_H
#define PASTEQUEARENA_REAL_H

#include <cmath>

namespace PastequeArena::Math {
    // PastequeArena needs to be deterministic, and thus, we need some deterministic
    // floating point type.
    // Currently, the options are:
    //   - float/double
    //   - some custom fixed-point integer
    // We're setting this type up, so we can easily (kinda) switch between different
    // "implementation" of real numbers. Same goes for functions in the Math namespace.
    //
    // Right now, we're using floating points because it's easy, convenient, and
    // it might work deterministically with some efforts.
    // If it doesn't, we'll replace real with something else.
    using real = float;

    inline real Zero = 0;

    inline real Sqrt(real x) {
        return std::sqrtf(x);
    }

    template <typename T>
    inline T Max(T a, T b) {
        if (a > b) {
            return a;
        } else {
            return b;
        }
    }

    template <typename T>
    inline T Min(T a, T b) {
        if (a < b) {
            return a;
        } else {
            return b;
        }
    }

    // min <= a <= max
    template <typename T>
    inline T Clamp(T a, T min, T max) {
        if (a < min) {
            return min;
        } else if (a > max) {
            return max;
        } else {
            return a;
        }
    }

    inline real FloatToReal(float f) {
        return f; // How convenient!
    }

    inline real DoubleToReal(double d) {
        return (real)d;
    }

    inline real Int32ToReal(int32_t i) {
        return (real)i;
    }

    inline real Int64ToReal(int64_t l) {
        return (real)l;
    }
}

// Export the real type to the PastequeArena namespace for convenience.
namespace PastequeArena {
    using Math::real;
}

#endif //PASTEQUEARENA_REAL_H
