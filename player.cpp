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

static const uint8_t recSize = 50; // Player rectangle size 
static const float updateTime = 0.084f; // Update time for the custom timer
static float timer = 0.0f; // Custom timer?

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

/* ----------------------- Public Functions ----------------------- */
/* ---------------------------------------------------------------- */

void UpdatePlayer(Player& player, bool isGrounded)
{
    // AnimatePlayer(player, 4.0f, 9.0f, 2, (GetInputMovement() != 0));

    AnimateCharacter(player, 4.0f, 9.0f, 2, (GetInputMovement() != 0));

    if (IsKeyDown(KEY_LEFT_SHIFT)) player.speed = 0.45f;
    else player.speed = 0.2f;

    // Horizontal movement input
    if (GetInputMovement() == 2)
    {
        player.facing = -1.0f;
        player.body->velocity.x = player.speed;
    }
    else if (GetInputMovement() == 1)
    {
        player.facing = 1.0f;
        player.body->velocity.x = -player.speed;
    }

    const float jumpSpeed = (GetInputMovement() != 0) ? player.speed : 0.35f;

    // PrintS(BoolToString(GetInputMovement() != 0), 1);

    const bool isJump = (IsKeyDown(KEY_SPACE) && isGrounded || /* For rec objects */
        IsKeyDown(KEY_SPACE) && player.body->isGrounded /* For rec physics objects */) ? true : false;

    // Vertical movement input checking if player physics body is grounded
    if (isJump)
    {
        player.body->velocity.y = (GetInputMovement() != 0) ? -jumpSpeed * 6 : -jumpSpeed * 4;
    }

    // Update player sound
    if (GetInputMovement() != 0)
    {
        timer += GetFrameTime() * 0.22f;
        if (timer >= updateTime)
        {
            timer = 0.0f;
            PlaySound(player.walkStepSound);
        }
    }
    if (isJump)
    {
        PlaySound(player.jumpSound);
    }

    // PrintS(BoolToString(isGrounded), 1);

    PhysicsAddForce(player.body, (Vector2){ 0.0f, 9.8f * player.gravityScale });

    player.rectangle = (Rectangle){ player.body->position.x - 30.0f, player.body->position.y - 30.0f, recSize, recSize };
}

void DrawPlayer(const Player& player)
{
    DrawTexturePro(
        player.texture,
        player.source,
        player.dest,
        Vector2Zero(),
        0.0f,
        WHITE);
}

Rectangle GetPlayerRectangle(const Player& player)
{
    return (Rectangle){ player.body->position.x, player.body->position.y, recSize, recSize };
}

Player CreatePlayer(Vector2 position)
{
    Player player;
    player.facing = 1.0f;
    player.currentFrame = 0.0f;
    player.dest = (Rectangle){ 0, 0, 0, 0 };
    player.source = (Rectangle){ 0, 0, 0, 0 };
    player.body = CreatePhysicsBodyRectangle(position, recSize, recSize, 1);
    player.body->freezeOrient = true; // Constrain body
    player.body->position = position;
    player.body->mass = 2.0f;
    player.gravityScale = 14.0f;
    player.texture = LoadTexture("resources/robo.png");
    player.walkStepSound = LoadSound("resources/walk_step.wav");
    player.jumpSound = LoadSound("resources/jump.wav");

    return player;
}

void DeletePlayer(Player& player)
{
    UnloadSound(player.jumpSound);
    UnloadSound(player.walkStepSound);
    UnloadTexture(player.texture);
}