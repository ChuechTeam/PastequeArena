#ifndef PASTEQUEARENA_FRAMEDATAEDITORSCENE_H
#define PASTEQUEARENA_FRAMEDATAEDITORSCENE_H

#include "Engine.h"

namespace PastequeArena {

    class FrameDataEditorScene : public Scene {
    public:
        static std::unique_ptr<FrameDataEditorScene> Create(Engine& engine);

    protected:
        explicit FrameDataEditorScene(Engine& engine) : Scene(engine) {}
    };

} // PastequeArena

#endif //PASTEQUEARENA_FRAMEDATAEDITORSCENE_H
