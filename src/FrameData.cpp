#include "FrameData.h"

using namespace PastequeArena;

std::ostream& PastequeArena::operator<<(std::ostream& os, const FrameData::IntVec2& v) {
    os << v.x << "," << v.y;
    return os;
}

std::ostream& PastequeArena::operator<<(std::ostream& os, const FrameData::IntRect& r) {
    os << r.x << "," << r.y << "," << r.width << "," << r.height;
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
        }
    }
}

