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

#include <memory>
#include "raylib.h"
#include "stdlib.h"
#include "camera.hpp"
#include "raymath.h"
#include "extras/physac.h"

#define MAX_GROUNDS 12
#define MAX_STEELS 12

struct Ground
{
    inline ~Ground() 
    { 
        DestroyPhysicsBody(body);
    }

    void Draw() const;

    PhysicsBody body = nullptr;
};

struct Steel
{
    inline ~Steel() 
    { 
        DestroyPhysicsBody(body);
    }

    void Draw() const;

    PhysicsBody body = nullptr;
};

void InitWorld();
void UpdateGround();
void InitBackground();
void DrawBackground();
void CleanBackground();
void DrawWorldVertex();
void DrawWorldTexture();
void UpdateWorld(bool drawVertex, bool drawTexture);
void DestroyWorld();