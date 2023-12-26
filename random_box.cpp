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

#include "random_box.hpp"

static std::unique_ptr<std::vector<std::unique_ptr<RandomBox>>> objects = {};
static uint8_t objectSize = 55;
static float randomBoxTimer = 0.0f;
static bool isActive = false;

void InitRandomBox(Vector2 playerPos, const float playerFacing)
{
    objects.reset();
    
    objects = std::make_unique<std::vector<std::unique_ptr<RandomBox>>>();

    objects->push_back(std::make_unique<RandomBox>());
    objects->push_back(std::make_unique<RandomBox>());

    const float x = (playerFacing == -1.0f) ? playerPos.x + 100 : playerPos.x - 100;

    objects->at(0)->body = CreatePhysicsBodyRectangle((Vector2){ x, playerPos.y - 100.0f }, objectSize, objectSize, 1);
    objects->at(0)->body->enabled = true;
    objects->at(0)->body->freezeOrient = true;

    objects->at(1)->body = CreatePhysicsBodyRectangle((Vector2){ x * 1.2f, playerPos.y - 100.0f }, objectSize, objectSize, 1);
    objects->at(1)->body->enabled = true;
    objects->at(1)->body->freezeOrient = true;

    randomBoxTimer = 0.0f;
}

void UpdateRandomBox(const Rectangle& cameraRec, const Vector2& playerPos, const float playerFacing)
{
    if (isActive)
    {
        for (auto it = objects->begin(); it != objects->end();)
        {
            const Rectangle updateCameraRec = { cameraRec.x, cameraRec.y, cameraRec.width * 1.5f, cameraRec.height * 1.5f };

            if (!CheckCollisionCircleRec((*it)->body->position, (float)objectSize, updateCameraRec))
            {
                it = objects->erase(it);
                PrintS("A box destroyed (out of camera)", true);
            }
            else
            {
                it++;
            }
        }
    }
    else
    {
        randomBoxTimer += GetFrameTime();

        if (randomBoxTimer > 10.0f)
        {
            InitRandomBox(playerPos, playerFacing);
            isActive = true;
        }
    }

    if (objects != nullptr)
    {
        if (objects->empty()) isActive = false;
    }

    // PrintI(objects->size(), true);
}

void DrawRandomBox()
{
    if (isActive)
    {
        for (auto it = objects->begin(); it != objects->end(); it++)
        {
            DrawRectangleV(
                (Vector2){ (*it)->body->position.x - objectSize / 2, (*it)->body->position.y - objectSize / 2 }, 
                (Vector2){ (float)objectSize, (float)objectSize },
                GOLD
            );
        }
    }
}
