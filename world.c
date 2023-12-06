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

#include "world.h"

Floor* pFloors[6] = {};
Ground* pGrounds[5] = {};
Vector2 newGround3Pos = {};
bool drawWorldTexture = true;
Texture2D mainBackgroundTexture = {};
float groundRotation = 0.0f;
bool drawWorlVertex = true;
float amplitude = 50.0f;
float frequency = 2.0f;

void InitWorld()
{
    const float screenWidth  = GetScreenWidth();
    const float screenHeight = GetScreenHeight();

    // Allocate memory for each floor
    pFloors[0] = (Floor*)malloc(sizeof(Floor));
    pFloors[1] = (Floor*)malloc(sizeof(Floor));
    pFloors[2] = (Floor*)malloc(sizeof(Floor));
    pFloors[3] = (Floor*)malloc(sizeof(Floor));
    pFloors[4] = (Floor*)malloc(sizeof(Floor));
    pFloors[5] = (Floor*)malloc(sizeof(Floor));

    *pFloors[0] = CreateFloor("floor.png", (Vector2){ screenWidth / 2.0f, (float)screenHeight }, (float)screenWidth, 100, 10);
    *pFloors[1] = CreateFloor("floor.png", (Vector2){ screenWidth / 2.0f * 2 + 600.0f, (float)screenHeight }, (float)screenWidth, 100, 10);
    *pFloors[2] = CreateFloor("floor.png", (Vector2){ screenWidth / 2.0f * 3 + 600.0f * 2, (float)screenHeight }, (float)screenWidth, 100, 10);
    *pFloors[3] = CreateFloor("floor.png", (Vector2){ screenWidth / 2.0f * 4 + 600.0f * 3, (float)screenHeight }, (float)screenWidth, 100, 10);
    *pFloors[4] = CreateFloor("floor.png", (Vector2){ screenWidth / 2.0f * 5 + 600.0f * 4, (float)screenHeight }, (float)screenWidth, 100, 10);
    *pFloors[5] = CreateFloor("floor.png", (Vector2){ screenWidth / 2.0f * 6 + 600.0f * 5, (float)screenHeight }, (float)screenWidth, 100, 10);

    // Allocate memory for each ground
    pGrounds[0] = (Ground*)malloc(sizeof(Ground));
    pGrounds[1] = (Ground*)malloc(sizeof(Ground));
    pGrounds[2] = (Ground*)malloc(sizeof(Ground));
    pGrounds[3] = (Ground*)malloc(sizeof(Ground));
    pGrounds[4] = (Ground*)malloc(sizeof(Ground));

    *pGrounds[0] = CreateGround("ground.png", (Vector2){ screenWidth * 0.25f, screenHeight * 0.6f }, screenWidth * 0.25f, 10, 10);
    *pGrounds[1] = CreateGround("ground.png", (Vector2){ screenWidth * 0.25f + 600.0f, screenHeight * 0.5f }, screenWidth * 0.25f, 10, 10);
    *pGrounds[2] = CreateGround("ground.png", (Vector2){ screenWidth * 0.25f + 600.0f * 3, screenHeight * 0.3f }, screenWidth * 0.25f, 10, 10);
    *pGrounds[3] = CreateGround("ground.png", (Vector2){ screenWidth * 0.25f + 600.0f * 4, screenHeight * 0.6f}, screenWidth * 0.25f, 10, 10);
    *pGrounds[4] = CreateGround("ground.png", (Vector2){ screenWidth * 0.25f + 600.0f * 5, screenHeight * 0.6f }, screenWidth * 0.25f, 10, 10);

    // Disable dynamics for floor physics bodies
    for (int i = 0; i < 6; i++)
    {
        pFloors[i]->body->enabled = false;
    }

    // Disable dynamics for ground physics bodies
    for (int i = 0; i < 5; i++)
    {
        pGrounds[i]->body->enabled = false;
        pGrounds[i]->isRotated = true;
    }

    pGrounds[0]->isRotated = false;
    pGrounds[2]->isRotated = false;
    pGrounds[4]->isRotated = false;
}

Floor CreateFloor(const char* texture, Vector2 position, float width, float height, float density)
{
    Floor floor;
    floor.texture = LoadTexture(texture);
    floor.body = CreatePhysicsBodyRectangle(position, width, height, density);

    return floor;
}

Ground CreateGround(const char* texture, Vector2 position, float width, float height, float density)
{
    Ground ground;
    ground.texture = LoadTexture(texture);
    Vector2 bodyPosition = (Vector2){ position.x + ground.texture.width / 2 + 100.0f, position.y - ground.texture.height / 2 - 40.0f };
    ground.body = CreatePhysicsBodyRectangle(bodyPosition, width, height, density);

    return ground;
}

void UpdateGround()
{
    groundRotation += 0.01f;

    // Update
    // Oscillating motion for the ground using lerp
    newGround3Pos = (Vector2){ pGrounds[2]->body->position.x, pGrounds[2]->body->position.y + amplitude * sinf(GetTime() * frequency) };

    pGrounds[2]->body->position = Vector2Lerp( // Adjust the interpolation factor for smoother motion
                                pGrounds[2]->body->position, 
                                newGround3Pos, 
                                0.1f);
    
    // Set the physics body rotation
    for (int i = 0; i < 5; i++)
    {
        const float rotation = (pGrounds[i]->isRotated) ? groundRotation : 0.0f;
        SetPhysicsBodyRotation(pGrounds[i]->body, rotation);
    }
}

void DrawGround()
{
    for (int i = 0; i < 5; i++)
    {
        const float rotation = (pGrounds[i]->isRotated) ? groundRotation : 0.0f;
        Rectangle sourceRec = { 0, 0, (float)pGrounds[i]->texture.width, (float)pGrounds[i]->texture.height };

        // Draw rotated texture based on the center of each ground object
        DrawTexturePro(
            pGrounds[i]->texture,
            sourceRec,
            (Rectangle){ pGrounds[i]->body->position.x, pGrounds[i]->body->position.y, (float)pGrounds[i]->texture.width, (float)pGrounds[i]->texture.height },
            (Vector2){ (float)pGrounds[i]->texture.width / 2, (float)pGrounds[i]->texture.height / 2 }, // Rotation point at the center
            rotation * 57.295f,
            WHITE
        );
    }
}

void DrawFloor()
{
    for (int i = 0; i < 6; i++)
    {
        DrawTextureV(
            pFloors[i]->texture, 
            (Vector2){ pFloors[i]->body->position.x - 400.f, pFloors[i]->body->position.y - 50.f }, 
            WHITE);
    }
}

void DeleteFloor(Floor* floor)
{
    UnloadTexture(floor->texture);
}

void DeleteGround(Ground* ground)
{
    UnloadTexture(ground->texture);
}

void DrawWorldTexture()
{
    if (drawWorldTexture)
    {
        DrawGround();
        DrawFloor();
    }
}

void DrawWorldVertex()
{
    if (drawWorlVertex)
    {
        // Draw created physics bodies
        int bodiesCount = GetPhysicsBodiesCount();
        for (int i = 0; i < bodiesCount; i++)
        {
            PhysicsBody body = GetPhysicsBody(i);

            int vertexCount = GetPhysicsShapeVerticesCount(i);
            for (int j = 0; j < vertexCount; j++)
            {
                // Get physics bodies shape vertices to draw lines
                // Note: GetPhysicsShapeVertex() already calculates rotation transformations
                Vector2 vertexA = GetPhysicsShapeVertex(body, j);

                int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);   // Get next vertex or first to close the shape
                Vector2 vertexB = GetPhysicsShapeVertex(body, jj);

                DrawLineV(vertexA, vertexB, GREEN);     // Draw a line between two vertex positions
            }
        }
    }
}

void CleanupFloor()
{
    for (int i = 0; i < 6; i++)
    {
        UnloadTexture(pFloors[i]->texture);
        free(pFloors[i]);
    }
}

void CleanupGround()
{
    for (int i = 0; i < 5; i++)
    {
        UnloadTexture(pGrounds[i]->texture);
        free(pGrounds[i]);
    }
}

void InitBackground()
{
    mainBackgroundTexture = LoadTexture("background0.png");
}

void DrawBackground()
{
    DrawTextureEx(mainBackgroundTexture, {}, 0.0f, 0.5f, WHITE);
}

void CleanBackground()
{
    UnloadTexture(mainBackgroundTexture);
}

void UpdateWorld(bool drawVertex, bool drawTexture)
{
    drawWorlVertex = drawVertex;
    drawWorldTexture = drawTexture;
}