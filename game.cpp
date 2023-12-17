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

// Define a threshold for falling below the screen
#define FALL_THRESHOLD 5000.0f

#define PHYSAC_IMPLEMENTATION
#include "extras/physac.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "2D Platformer");
    InitRandomStone();
    InitBackground();
    InitPhysics();
    InitBullet();
    InitWorld();

    SetPhysicsGravity(0.0f, 0.2f); // Adjust the magnitude

    Player player = CreatePlayer((Vector2){ screenWidth / 2.0f, screenHeight / 2.0f }, "resources/robo.png");
    Camera2D camera = CreateCamera2D();

    CheckBox isDrawWorldVertex  = CreateCheckBox();
    CheckBox isDrawWorldTexture = CreateCheckBox();

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdatePhysics();                                                // Update physics system
        UpdatePlayer(&player, IsPlayerGrounded());                                          // Update player
        UpdateCamera2D(&camera, player.body->position);                 // Update camera
        UpdateAndSpawnBullet(player.body->position, player.facing);     // Update and bullet
        
        UpdateWorld(
            isDrawWorldVertex.flag, 
            isDrawWorldTexture.flag, 
            GetPlayerRectangle(&player)
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
            DrawCheckBox(&isDrawWorldVertex,  "Draw World Vertex",  (Vector2){ 5.0f, 50.0f }, 20);
            DrawCheckBox(&isDrawWorldTexture, "Draw World Texture", (Vector2){ 5.0f, 90.0f }, 20);
            BeginMode2D(camera);
                DrawWorldTexture();
                DrawWorldVertex();
                DrawPlayer(&player);
                DrawBullet(player.body->position, false);
            EndMode2D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    DeletePlayer(&player);  // Delete the player
    CleanBackground();      // Clean the background
    ClosePhysics();         // Unitialize physics
    DestroyWorld();         // Destroy World
    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}