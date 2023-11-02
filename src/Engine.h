#ifndef PASTEQUEARENA_ENGINE_H
#define PASTEQUEARENA_ENGINE_H

#include <raylib-cpp.hpp>
#include <vector>
#include <array>
#include <cstdint>
#include "AssetLoader.h"

namespace PastequeArena {
    class Engine;

    class Scene {
    public:
        friend class Engine;

        explicit Scene(Engine& engine) : engine(engine) {}
        virtual ~Scene() = default;

    protected:
        virtual void Init() {}
        virtual void Update() {}
        virtual void Draw() {}
        virtual void Unload() {}

        Engine& engine;
        uint8_t index = -1;
    private:
        bool unloadPending = false; // Set by Engine in UnloadScene
    };

    class Engine {
    public:
        static constexpr int MaxScenes = 8;

        Engine();

        void GameLoop();

        void AddScene(std::unique_ptr<Scene>&& scene);
        void UnloadScene(Scene& scene);

        void Quit();

        AssetLoader& GetAssetLoader() { return assetLoader; }
        raylib::Window& GetWindow() { return window; }

    private:
        inline void RemoveScene(uint8_t sceneIdx);

        raylib::Window window;

        std::array<std::unique_ptr<Scene>, MaxScenes> scenes;
        std::vector<uint8_t> newSceneIndexes;
        std::vector<uint8_t> unloadSceneIndexes;
        uint8_t numScenes = 0;

        bool quitPending = false;

        AssetLoader assetLoader;
    };
}

#endif //PASTEQUEARENA_ENGINE_H
