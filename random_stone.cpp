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

static std::unique_ptr<std::vector<std::unique_ptr<RandomStone>>> objects = {};
static uint8_t objectSize = 45;
static float randomStoneTimer = 0.0f;

bool isActive = false;

void InitRandomStone(Vector2 playerPos)
{
    objects.reset();
    
    objects = std::make_unique<std::vector<std::unique_ptr<RandomStone>>>();

    objects->push_back(std::make_unique<RandomStone>());
    objects->push_back(std::make_unique<RandomStone>());

    objects->at(0)->body = CreatePhysicsBodyCircle((Vector2){ playerPos.x - 150.0f, playerPos.y - 200.0f }, objectSize, 10);
    objects->at(0)->body->enabled = true;

    objects->at(1)->body = CreatePhysicsBodyCircle((Vector2){ playerPos.x + 150.0f, playerPos.y - 200.0f }, objectSize, 10);
    objects->at(1)->body->enabled = true;

    randomStoneTimer = 0.0f;
}

void UpdateRandomStone(const Rectangle& cameraRec, const Vector2& playerPos)
{
    if (isActive)
    {
        for (auto it = objects->begin(); it != objects->end();)
        {
            const Rectangle updateCameraRec = { cameraRec.x, cameraRec.y, cameraRec.width * 1.5f, cameraRec.height * 1.5f };

            if (!CheckCollisionCircleRec((*it)->body->position, (float)objectSize, updateCameraRec))
            {
                it = objects->erase(it);
                PrintS("A stone destroyed (out of camera)", true);
            }
            else
            {
                it++;
            }
        }
    }
    else
    {
        randomStoneTimer += GetFrameTime();

        if (randomStoneTimer > 10.0f)
        {
            InitRandomStone(playerPos);
            isActive = true;
        }
    }

    if (objects != nullptr)
    {
        if (objects->empty()) isActive = false;
    }

    // PrintI(objects->size(), true);
}

void DrawRandomStone()
{
    if (isActive)
    {
        for (auto it = objects->begin(); it != objects->end(); it++)
        {
            DrawCircle(
                (*it)->body->position.x, 
                (*it)->body->position.y, 
                objectSize, 
                BROWN
            );
        }
    }
}