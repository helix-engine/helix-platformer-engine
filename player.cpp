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

#include "player.hpp"

static uint8_t frameCounter = 0; // -> AnimatePlayer()
static uint8_t recSize[2] = { 50, 50 };

/* ---------------------- Private Functions ----------------------- */
/* ---------------------------------------------------------------- */

/*
* Horizontal movement input:
* 1 -> left, 2 -> right, 0 -> idle
*/
uint8_t GetInputMovement()
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
    uint8_t numFrames, 
    bool animate)
{
    player->source = (Rectangle){
        .x      = player->currentFrame * (float)player->texture.width / numFrames,
        .y      = 0.0f, 
        .width  = player->facing * (float)player->texture.width / numFrames,
        .height = (float)player->texture.height
    };

    player->dest = (Rectangle){
        .x      = player->body->position.x - 30.0f, 
        .y      = player->body->position.y - 30.0f,
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

void UpdatePlayer(Player* player, bool isGrounded)
{
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
    if (IsKeyDown(KEY_SPACE) && isGrounded || /* For rec objects */
            IsKeyDown(KEY_SPACE) && player->body->isGrounded /* For rec physics objects */)
    {
        player->body->velocity.y = (GetInputMovement() != 0) ? -jumpSpeed * 6 : -jumpSpeed * 4;
    }

    // PrintS(BoolToString(isGrounded), 1);

    PhysicsAddForce(player->body, (Vector2){ 0.0f, 9.8f * player->gravityScale });
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

Rectangle GetPlayerRectangle(const Player* player)
{
    return (Rectangle){ player->body->position.x, player->body->position.y, recSize[0], recSize[1] };
}

Player CreatePlayer(Vector2 position, const char* texture)
{
    Player player;
    player.facing = 1.0f;
    player.currentFrame = 0.0f;
    player.dest = (Rectangle){ 0, 0, 0, 0 };
    player.source = (Rectangle){ 0, 0, 0, 0 };
    player.body = CreatePhysicsBodyRectangle(position, recSize[0], recSize[1], 1);
    player.body->freezeOrient = true; // Constrain body
    player.body->position = position;
    player.body->mass = 2.0f;
    player.texture = LoadTexture(texture);
    player.gravityScale = 14.0f;

    return player;
}

void DeletePlayer(Player* player)
{
    UnloadTexture(player->texture);
}