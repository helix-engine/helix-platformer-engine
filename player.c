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

#include "player.h"

/* -> AnimatePlayer() */
static int frameCounter = 0;

/* ---------------------- Private Functions ----------------------- */
/* ---------------------------------------------------------------- */

/*
* Horizontal movement input:
* 1 -> left, 2 -> right, 0 -> idle
*/
unsigned char GetInputMovement()
{
    // Horizontal movement input
    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) return 1;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) return 2;

    return 0;
}

void AnimatePlayer(
    Player* player, 
    float scale, 
    float frameSpeed, 
    int numFrames, 
    bool animate)
{
    player->source = (Rectangle){
        .x      = player->currentFrame * (float)player->texture.width / numFrames,
        .y      = 0.0f, 
        .width  = player->facing * (float)player->texture.width / numFrames,
        .height = (float)player->texture.height
    };

    player->dest = (Rectangle){
        .x      = player->position.x - 30.0f, 
        .y      = player->position.y - 30.0f,
        .width  = scale * (float)player->texture.width / numFrames,
        .height = scale * (float)player->texture.height
    };

    if (animate)
    {
        frameCounter++;
        if (frameCounter >= (GetFPS() / frameSpeed))
        {
            frameCounter = 0;
            player->currentFrame++;
            if (player->currentFrame > numFrames) 
            {
                player->currentFrame = 0;
            }
        }
    }
}

/* ----------------------- Public Functions ----------------------- */
/* ---------------------------------------------------------------- */

void UpdatePlayer(Player* player)
{
    player->position = player->body->position;

    AnimatePlayer(player, 4.0f, 6.0f, 2, (GetInputMovement() != 0));

    if (IsKeyDown(KEY_LEFT_SHIFT)) player->speed = 0.45f;
    else player->speed = 0.2f;

    // Horizontal movement input
    if (GetInputMovement() == 2)
    {
        player->facing = -1.0f;
        player->body->velocity.x = player->speed;
    }
    else if (GetInputMovement() == 1)
    {
        player->facing = 1.0f;
        player->body->velocity.x = -player->speed;
    }

    const float jumpSpeed = (GetInputMovement() != 0) ? player->speed : 0.35f;

    // PrintS(BoolToString(GetInputMovement() != 0), 1);

    // Vertical movement input checking if player physics body is grounded
    if (IsKeyDown(KEY_SPACE) && player->body->isGrounded) 
    {
        player->body->velocity.y = (GetInputMovement() != 0) ? -jumpSpeed * 6 : -jumpSpeed * 4;
    }
}

void DrawPlayer(const Player* player)
{
    DrawTexturePro(
        player->texture,
        player->source,
        player->dest,
        Vector2Zero(),
        0.0f,
        WHITE);
}

Player CreatePlayer(Vector2 position, const char* texture)
{
    Player player;
    player.facing = 1.0f;
    player.currentFrame = 0.0f;
    player.dest = (Rectangle){ 0, 0, 0, 0 };
    player.source = (Rectangle){ 0, 0, 0, 0 };
    player.body = CreatePhysicsBodyRectangle(position, 50, 50, 1);
    player.body->freezeOrient = true; // Constrain body
    player.body->position = position;
    player.texture = LoadTexture(texture);

    return player;
}

void DeletePlayer(Player* player)
{
    UnloadTexture(player->texture);
}