#include <raylib-cpp.hpp>
#include <stdio.h>
#include <raymath.h>
#include <stdint.h>
#include <raygui.h>

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    raylib::Window window(screenWidth, screenHeight, "Pasteque ARENA");
    window.SetState(FLAG_WINDOW_RESIZABLE);
    window.SetConfigFlags(FLAG_MSAA_4X_HINT);

    GuiLoadStyleDefault();

    // SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!window.ShouldClose())    // Detect window close button or ESC key
    {
        // Update

        // Draw
        //----------------------------------------------------------------------------------
        window.BeginDrawing();

        window.ClearBackground(RAYWHITE);

        window.DrawFPS(0, 0);

        raylib::DrawText("Salut", 300, 200, 20, RED);

        window.EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
