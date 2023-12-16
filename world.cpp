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

#include "world.hpp"

Vector2 newGround3Pos = {};
bool drawWorldTexture = true;
Texture2D mainBackgroundTexture = {};
float groundRotation = 0.0f;
bool drawWorlVertex = true;
float amplitude = 50.0f;
float frequency = 2.0f;

int numGrounds = 0; // Variable to keep track of the number of colliding objects

Rectangle groundRecData[MAX_GROUNDS];

std::shared_ptr<Ground> pGrounds[MAX_GROUNDS] = {};

Texture2D groundTexture;

void InitWorld()
{
    const float width = 800.0f;
    const float height = 450.0f;

    groundTexture = LoadTexture("resources/ground.png");

    for (int i = 0; i < MAX_GROUNDS; i++)
    {
        pGrounds[i] = nullptr;
        groundRecData[i] = (Rectangle){ width / 2 * (i + 1) + 600.0f * i, height, width, 100.0f };
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
    DrawRectangleLinesEx(GetCameraRectangle(), 2, GREEN);
}

void InitBackground()
{
    mainBackgroundTexture = LoadTexture("resources/background0.png");
}

void DrawBackground()
{
    if (drawWorldTexture)
    {
        DrawTextureEx(mainBackgroundTexture, {}, 0.0f, 0.5f, WHITE);
    }
}

void CleanBackground()
{
    UnloadTexture(mainBackgroundTexture);
}

void UpdateWorld(bool drawVertex, bool drawTexture)
{
    // Reset the counter for each frame
    numGrounds = 0;

    for (int i = 0; i < MAX_GROUNDS; i++)
    {
        Rectangle inViewRec = { 
            GetCameraRectangle().x, 
            GetCameraRectangle().y, 
            GetCameraRectangle().width  * 2, 
            GetCameraRectangle().height * 2 
            };
        if (CheckCollisionRecs(inViewRec, groundRecData[i]))
        {
            // Collision detected, store the colliding object on the heap
            auto newObject = std::make_shared<Ground>();  
            
            // Store the data
            newObject->body = CreatePhysicsBodyRectangle(
                (Vector2){ groundRecData[i].x, groundRecData[i].y }, 
                groundRecData[i].width, 
                groundRecData[i].height, 10
            ); 
            newObject->body->enabled = false;
            pGrounds[numGrounds] = newObject;
            numGrounds++;
        }
        else 
        {
            // No collision, delete the physics body and reset the pointer
            if (pGrounds[i] != nullptr)
            {
                pGrounds[i].reset();
            }
        }
    }

    drawWorlVertex = drawVertex;
    drawWorldTexture = drawTexture;
}

void DrawGroundTexture(Vector2 position)
{
    DrawTextureV(
        groundTexture, 
        position,
        WHITE);
}

void Ground::Draw() const
{
    DrawGroundTexture((Vector2){ body->position.x - 400.f, body->position.y - 50.f });
}

void DrawWorldTexture()
{
    if (drawWorldTexture)
    {
        for (const auto& ground : pGrounds)
        {
            if (ground != nullptr)
            {
                ground->Draw();
            }
        }
    }
}

void DestroyWorld()
{
    UnloadTexture(groundTexture);
}