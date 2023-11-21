#ifndef PASTEQUEARENA_FRAMEDATA_H
#define PASTEQUEARENA_FRAMEDATA_H

#include "FixedInt.h"
#include <string>
#include <strstream>
#include "Math/Vec.h"
#include "Math/Rect.h"

namespace PastequeArena {
    struct FrameData {
        using PixelVec = Math::Vec2<int32_t>;

        struct Collider {
            PixelVec origin;
            PixelVec extent;
            bool isHitBox = false;
            bool isHurtBox = false;
        };
        struct Frame {
            Math::Rect<int32_t> textureRect;
            PixelVec pivot;

            std::vector<Collider> colliders;
        };

        std::string image;
        float worldScale = 1.0f;

        std::vector<Frame> frames;

        void WriteToStream(std::ostream& stream);
    };
}


#endif //PASTEQUEARENA_FRAMEDATA_H
