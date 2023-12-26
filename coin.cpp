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

#include "coin.hpp"

static Texture2D texture = {};
static std::vector<Coin> objects = {};

void InitCoin()
{
    texture = LoadTexture("");

    for (uint8_t i = 0; i < 100; i++)
    {
        objects.push_back(Coin(
            (Vector2){ (float)GetRandomValue(0, 100000), (float)GetRandomValue(100, 300) },
            80, i  
        ));
    }
}

void UpdateCoin(const Rectangle& playerRec)
{
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        if (CheckCollisionRecs(it->GetRectangle(), playerRec))
        {
            objects.erase(it);
            break; // Exit the loop after erasing one element
        }
    }
}

void DrawCoin()
{
    for (const auto& object : objects)
    {
        object.Draw();
    }
}

void DestroyCoin()
{
    UnloadTexture(texture);
}

uint8_t GetCoinCount()
{
    return objects.size();
}