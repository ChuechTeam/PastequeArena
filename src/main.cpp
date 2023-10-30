#include <raylib-cpp.hpp>
#include <stdio.h>
#include <raymath.h>
#include <stdint.h>
#include <raygui.h>
#include <AssetLoader.h>

using namespace PastequeArena;

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------

#if defined(PLATFORM_ANDROID)
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
#else
    const int screenWidth = 800;
    const int screenHeight = 450;
#endif

    raylib::Window window(screenWidth, screenHeight, "Pasteque ARENA");
    window.SetState(FLAG_WINDOW_RESIZABLE);
    window.SetConfigFlags(FLAG_MSAA_4X_HINT);

    GuiLoadStyleDefault();

    // SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    raylib::Vector2 touch;

    AssetLoader loader;
    raylib::Texture2D tex = loader.LoadTexture("choc.png");

    // Main game loop
    while (!window.ShouldClose())    // Detect window close button or ESC key
    {
        // Update

        // Draw
        //----------------------------------------------------------------------------------
        window.BeginDrawing();

        window.ClearBackground(RAYWHITE);

        window.DrawFPS(0, 0);

        raylib::DrawText("Hello world!!", 300, 200, 48, RED);
        raylib::DrawText(":D", 300, 300, 48, RED);

        touch = GetTouchPosition(0);
        tex.Draw(touch - raylib::Vector2(tex.GetSize()) / 2);

        window.EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
