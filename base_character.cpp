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

#include "base_character.hpp"

static uint8_t frameCounter = 0;

void AnimateCharacter(
    BaseCharacter& self,
    float scale, 
    float frameSpeed, 
    uint8_t numFrames, 
    bool animate)
{
    self.source = (Rectangle){
        .x      = self.currentFrame * (float)self.texture.width / numFrames,
        .y      = 0.0f, 
        .width  = self.facing * (float)self.texture.width / numFrames,
        .height = (float)self.texture.height
    };

    self.dest = (Rectangle){
        .x      = self.body->position.x - 30.0f, 
        .y      = self.body->position.y - 30.0f,
        .width  = scale * (float)self.texture.width / numFrames,
        .height = scale * (float)self.texture.height
    };

    if (animate)
    {
        frameCounter++;
        if (frameCounter >= (GetFPS() / frameSpeed))
        {
            frameCounter = 0;
            self.currentFrame++;
            if (self.currentFrame > numFrames) 
            {
                self.currentFrame = 0;
            }
        }
    }
}