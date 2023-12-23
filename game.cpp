// Copyright (c) 2023 Wildan R Wijanarko (@wildan9)
//
// This software is provided ‘as-is’, without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.

// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:

// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.

// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.

// 3. This notice may not be removed or altered from any source
// distribution.

#include "game.hpp"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "2D Platformer");
    InitAudioDevice();
    InitRandomStone();
    InitBackground();
    InitPhysics();
    InitBullet();
    InitWorld();

    SetPhysicsGravity(0.0f, 0.2f); // Adjust the magnitude

    Player player = CreatePlayer((Vector2){ screenWidth / 2.0f, screenHeight / 2.0f });
    Camera2D camera = CreateCamera2D();

    bool isDrawWorldVertex  = true;
    bool isDrawWorldTexture = true;
    bool isDrawBulletLine   = true;
    bool isRotateSteels     = false;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdatePhysics();                                                // Update physics system
        UpdatePlayer(player, IsPlayerGrounded());                       // Update player
        UpdateCamera2D(&camera, player.body->position);                 // Update camera
        UpdateAndSpawnBullet(player.body->position, player.facing);     // Update and spwan bullet
        
        UpdateWorld(
            isDrawWorldVertex, 
            isDrawWorldTexture,
            isRotateSteels, 
            GetPlayerRectangle(player)
        ); // Update world

        // Check if the player falls
        if (player.body->position.y > FALL_THRESHOLD)
        {
            // Reset player position
            player.body->position = (Vector2){ player.body->position.x - 200.0f, -1000.0f };

            PrintS("Reset player position", 1);
        }

        // PrintS(BoolToString(IsPlayerGrounded()), 1);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            DrawBackground();
            DrawFPS(0, 0);
            
            isDrawWorldVertex  = GuiCheckBox((Rectangle){ 5.0f, 50.0f + 40 * 0, 20, 20 }, "Draw World Vertex",  isDrawWorldVertex);
            isDrawWorldTexture = GuiCheckBox((Rectangle){ 5.0f, 50.0f + 40 * 1, 20, 20 }, "Draw World Texture", isDrawWorldTexture);
            isDrawBulletLine   = GuiCheckBox((Rectangle){ 5.0f, 50.0f + 40 * 2, 20, 20 }, "Draw Bullet Line",   isDrawBulletLine);
            isRotateSteels     = GuiCheckBox((Rectangle){ 5.0f, 50.0f + 40 * 3, 20, 20 }, "Rotate Steels",      isRotateSteels);

            BeginMode2D(camera);
                DrawWorldTexture();
                DrawWorldVertex();
                DrawPlayer(player);
                DrawBullet(player.body->position, isDrawBulletLine);
            EndMode2D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    DeletePlayer(player);  // Delete the player
    CleanBackground();      // Clean the background
    ClosePhysics();         // Unitialize physics
    DestroyWorld();         // Destroy World
    CloseAudioDevice();     // Close audio device
    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}