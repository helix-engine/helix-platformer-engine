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

#include "random_stone.hpp"

static RandomStone objects[2] = {};
static uint8_t objectSize = 45;

void InitRandomStone()
{
    objects[0].body = CreatePhysicsBodyCircle((Vector2){ 200, 300 }, objectSize, 10);
    objects[0].body->enabled = true;

    objects[1].body = CreatePhysicsBodyCircle((Vector2){ 500, 300 }, objectSize, 10);
    objects[1].body->enabled = true;
}

void DrawRandomStone()
{
    for (const auto& object : objects) 
    {
        DrawCircle(
            object.body->position.x, 
            object.body->position.y, objectSize, 
            BROWN
        );
    }
}