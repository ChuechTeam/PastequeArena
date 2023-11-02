#ifndef PASTEQUEARENA_ASSETLOADER_H
#define PASTEQUEARENA_ASSETLOADER_H

#include <raylib-cpp.hpp>
#include <vector>
#include <filesystem>

#ifndef PA_DEV_ASSETS_DIR
#define PA_DEV_ASSETS_DIR ""
#endif

#ifndef PA_PACKAGED
#define PA_PACKAGED 0
#endif

namespace PastequeArena {
    class AssetLoader {
    public:
        AssetLoader();

        // TODO:
        //   - What's the lifetime of an asset?
        //   - How long is it loaded into memory?
        //   - How to handle duplicate assets loaded from the same file (textures & fonts)?

        raylib::Image LoadImage(const char* path);
        raylib::Texture LoadTexture(const char *path);
        raylib::Font LoadFont(const char* path, int fontSize);

    private:
        std::filesystem::path assetRootPath;
    };

}

#endif //PASTEQUEARENA_ASSETLOADER_H
