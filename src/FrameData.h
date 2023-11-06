#ifndef PASTEQUEARENA_FRAMEDATA_H
#define PASTEQUEARENA_FRAMEDATA_H

#include "FixedInt.h"
#include <string>
#include <strstream>

namespace PastequeArena {
    struct FrameData {
        struct IntVec2 {
            int x = 0;
            int y = 0;

            friend std::ostream& operator<<(std::ostream& os, const IntVec2& v);
        };

        struct IntRect {
            int x = 0;
            int y = 0;
            int width = 0;
            int height = 0;

            friend std::ostream& operator<<(std::ostream& os, const IntRect& v);
        };

        struct Collider {
            IntVec2 origin;
            IntVec2 extent;
            bool isHitBox = false;
            bool isHurtBox = false;
        };
        struct Frame {
            IntRect textureRect;
            IntVec2 pivot;

            std::vector<Collider> colliders;
        };

        std::string image;
        float worldScale = 1.0f;

        std::vector<Frame> frames;

        void WriteToStream(std::ostream& stream);
    };
}


#endif //PASTEQUEARENA_FRAMEDATA_H
