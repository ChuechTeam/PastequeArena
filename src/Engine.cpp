#include "Engine.h"

#define RAYGUI_IMPLEMENTATION 1

#include "raygui.h"
#include <cassert>

namespace PastequeArena {
    Engine::Engine() {
#if defined(PLATFORM_ANDROID)
        const int screenWidth = GetScreenWidth();
        const int screenHeight = GetScreenHeight();
#else
        const int screenWidth = 800;
        const int screenHeight = 450;
#endif

        window.Init(screenWidth, screenHeight, "Pasteque ARENA");
        window.SetState(FLAG_WINDOW_RESIZABLE);
        window.SetConfigFlags(FLAG_MSAA_4X_HINT);

        GuiLoadStyleDefault();
    }

    void Engine::GameLoop() {
        while (!window.ShouldClose() && !quitPending) {    // Detect window close button or ESC key
            // Pre-Update stage
            // ----------------------------------------------------------------------------------

            // Call Init() on scenes that have been recently added.
            // During this stage, no scenes can be removed.
            if (!newSceneIndexes.empty()) {
                for (uint8_t i: newSceneIndexes) {
                    scenes[i]->Init();
                }
                newSceneIndexes.clear();
            }

            // Remove scenes that have been queued for unload.
            if (!unloadSceneIndexes.empty()) {
                for (uint8_t i: unloadSceneIndexes) {
                    scenes[i]->Unload();
                    RemoveScene(i);
                }
                unloadSceneIndexes.clear();
            }

            // Update stage
            // ----------------------------------------------------------------------------------

            // Update all scenes.
            for (int32_t i = 0; i < numScenes; i++) {
                scenes[i]->Update();
            }

            // Draw stage
            //----------------------------------------------------------------------------------
            window.BeginDrawing();

            window.ClearBackground(RAYWHITE);

            // Draw all scenes.
            for (int32_t i = 0; i < numScenes; i++) {
                scenes[i]->Draw();
            }

            DrawFPS(8, 8);

            window.EndDrawing();
            //----------------------------------------------------------------------------------
        }

        // Make sure to unload all scenes before quitting.
        for (int32_t i = 0; i < numScenes; i++) {
            scenes[i]->Unload();
        }

        CloseWindow();
    }

    void Engine::AddScene(std::unique_ptr<Scene>&& scene) {
        assert(scene != nullptr && &scene->engine == this);

        if (numScenes >= MaxScenes) {
            char errMsg[256];
            std::snprintf(errMsg, 255, "Cannot add scene %s: maximum number of scenes reached.", typeid(scene).name());
            throw std::runtime_error(errMsg);
        }

        scene->index = numScenes;
        scenes[numScenes] = std::move(scene);
        numScenes++;
        newSceneIndexes.push_back(numScenes - 1);
    }

    inline void Engine::RemoveScene(uint8_t sceneIdx) {
        assert(sceneIdx < numScenes);
        assert(newSceneIndexes.empty());

        // Swap with the last scene.
        scenes[sceneIdx] = std::move(scenes[numScenes - 1]);
        scenes[sceneIdx]->index = sceneIdx;
        numScenes--;
    }

    void Engine::UnloadScene(Scene& scene) {
        assert(&scene.engine == this);

        if (scene.unloadPending) {
            return; // Already queued for unload.
        }

        scene.unloadPending = true;
        unloadSceneIndexes.push_back(scene.index);
    }

    void Engine::Quit() {
        quitPending = true;
    }
}