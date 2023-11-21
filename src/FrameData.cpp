#include "FrameData.h"

using namespace PastequeArena;

std::ostream& operator<<(std::ostream& os, const Math::Vec2<int32_t>& v) {
    os << v.x << "," << v.y;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Math::Rect<int32_t>& r) {
    os << r.origin.x << "," << r.origin.y << "," << r.extent.x << "," << r.extent.y;
    return os;
}

int BoolToInt(bool b) {
    return b ? 1 : 0;
}

void FrameData::WriteToStream(std::ostream& stream) {
    stream << "image=" << image << std::endl;
    stream << "worldScale=" << worldScale << std::endl;
    for (const Frame& frame: frames) {
        stream << ":frame" << std::endl;
        stream << "  textureRect=" << frame.textureRect << std::endl;
        stream << "  pivot=" << frame.pivot << std::endl;

        for (const Collider& collider : frame.colliders) {
            stream << "  :collider" << std::endl;
            stream << "    origin=" << collider.origin << std::endl;
            stream << "    extent=" << collider.extent << std::endl;
            stream << "    isHitBox=" << BoolToInt(collider.isHitBox) << std::endl;
            stream << "    isHurtBox=" << BoolToInt(collider.isHurtBox) << std::endl;
            stream << "  :" << std::endl;
        }

        stream << ":" << std::endl;
    }
}

