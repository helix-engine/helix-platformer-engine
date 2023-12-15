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

Vector2 newGround3Pos = {};
bool drawWorldTexture = true;
Texture2D mainBackgroundTexture = {};
float groundRotation = 0.0f;
bool drawWorlVertex = true;
float amplitude = 50.0f;
float frequency = 2.0f;

int numFloors = 0; // Variable to keep track of the number of colliding objects

Rectangle floorRecData[MAX_COLLIDERS];

std::shared_ptr<Floor> pFloors[MAX_COLLIDERS] = {};

void InitWorld()
{
    const float screenHeight = GetScreenHeight();

    for (int i = 0; i < MAX_COLLIDERS; i++)
    {
        pFloors[i] = nullptr;
    }

    floorRecData[0] = (Rectangle){ 200.0f * 1,              (float)screenHeight, 450.0f, 100.0f };
    floorRecData[1] = (Rectangle){ 200.0f * 2 + 350.0f * 1, (float)screenHeight, 450.0f, 100.0f };
    floorRecData[2] = (Rectangle){ 200.0f * 3 + 350.0f * 2, (float)screenHeight, 450.0f, 100.0f };
    floorRecData[3] = (Rectangle){ 200.0f * 4 + 350.0f * 3, (float)screenHeight, 450.0f, 100.0f };
    floorRecData[4] = (Rectangle){ 200.0f * 5 + 350.0f * 4, (float)screenHeight, 450.0f, 100.0f };
    floorRecData[5] = (Rectangle){ 200.0f * 6 + 350.0f * 5, (float)screenHeight, 450.0f, 100.0f };
}

void DrawFloor()
{

}

void DrawWorldTexture()
{

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
    DrawRectangleLinesEx(GetCameraRectangle(), 12, GREEN);
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
    // Reset the counter for each frame
    numFloors = 0;

    for (int i = 0; i < MAX_COLLIDERS; i++)
    {
        if (CheckCollisionRecs(GetCameraRectangle(), floorRecData[i]))
        {
            // Collision detected, store the colliding object on the heap
            auto newObject = std::make_shared<Floor>();  
            
            // Store the data
            newObject->body = CreatePhysicsBodyRectangle(
                (Vector2){ floorRecData[i].x, floorRecData[i].y }, 
                floorRecData[i].width, 
                floorRecData[i].height, 10
            ); 
            newObject->body->enabled = false;
            pFloors[numFloors] = newObject;
            numFloors++;
        }
        else 
        {
            // No collision, delete the physics body and reset the pointer
            if (pFloors[i] != nullptr)
            {
                pFloors[i].reset();
            }
        }
    }

    std::cout << numFloors << std::endl;

    drawWorlVertex = drawVertex;
    drawWorldTexture = drawTexture;
}