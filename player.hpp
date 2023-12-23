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

#include "raylib.h"
#include "stdint.h"
#include "raymath.h"
#include "basic_io.hpp"
#include "extras/physac.h"

typedef struct Player {
    float speed;
    float facing;
    float currentFrame;
    float gravityScale;
    Rectangle dest;
    Rectangle source;
    Texture2D texture;
    PhysicsBody body;
    Sound walkStepSound;
    Sound jumpSound;
} Player;

void DeletePlayer(Player& player);
Player CreatePlayer(Vector2 position);
void DrawPlayer(const Player& player);
Rectangle GetPlayerRectangle(const Player& player);
void UpdatePlayer(Player& player, bool isGrounded);