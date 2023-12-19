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

#include "bullet.hpp"

Bullet bullets[MAX_BULLETS];
uint8_t bulletCount = 0;

void InitBullet() 
{
    for (uint8_t i = 0; i < MAX_BULLETS; i++) 
    {
        bullets[i].body = NULL;
        bullets[i].lifetime = 0.0f;
    }
}

Bullet* GetNextBullet() 
{
    if (bulletCount < MAX_BULLETS) 
    {
        return &bullets[bulletCount++];
    }
    return NULL;  // Pool is exhausted
}

void UpdateAndSpawnBullet(Vector2 position, float directionX) 
{
    // PrintI(bulletCount, 1);

    float dx = (directionX == -1.0f) ? position.x + 10.0f : position.x - 10.0f;
    float dy = position.y - 30.0f;

    for (uint8_t i = 0; i < bulletCount; i++) 
    {
        // Decrease lifetime
        bullets[i].lifetime -= GetFrameTime();

        // Remove bullets that have expired
        if (bullets[i].lifetime <= 0) 
        {
            // Destroy the physics body
            DestroyPhysicsBody(bullets[i].body);

            // Reduce the bullet count
            bullets[i] = bullets[bulletCount - 1];
            (bulletCount)--;
            i--; // Check the current index again since it's now a different bullet
        }

        // if (bullets[i].body != NULL) PrintS(BoolToString(bullets[i].body->isGrounded), 1);
    }

    // Spawn new bullets
    if (IsKeyPressed(KEY_C) && bulletCount < MAX_BULLETS) 
    {
        Bullet* newBullet = GetNextBullet();
        if (newBullet != NULL) 
        {
            newBullet->body = CreatePhysicsBodyCircle((Vector2){ dx, dy }, 8, 10);
            newBullet->lifetime = 3.0f;
            
            float forceX = (directionX == -1.0f) ? 800.0f : -800.0f;
            float forceY = 0.0f;
            PhysicsAddForce(newBullet->body, (Vector2){ forceX, forceY });
        }
    }
}

void DrawBullet(Vector2 playerPos, bool drawLine)
{
    const Color colors[5] = { RED, GREEN, BLUE, BROWN, PURPLE };

    if (bulletCount > 0)
    {
        for (uint8_t i = 0; i < bulletCount; i++) 
        {
            DrawCircle(
                bullets[i].body->position.x, 
                bullets[i].body->position.y, 8, 
                colors[i]
            );
            if (drawLine)
            {
                DrawLine(
                    playerPos.x, 
                    playerPos.y, 
                    bullets[i].body->position.x, 
                    bullets[i].body->position.y, 
                    colors[i]
                );
            } 
        }
    }
}