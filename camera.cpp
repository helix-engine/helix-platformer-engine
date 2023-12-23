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

#include "camera.hpp"

Rectangle cameraRec = { 0, 0, 0, 0 };

Camera2D CreateCamera2D()
{
    Camera2D camera;
    camera.target = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    camera.offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 1.2f };
    camera.rotation = 0.0f;
    camera.zoom = 0.6f;

    return camera;
}

void UpdateCamera2D(Camera2D& camera, Vector2 target)
{
    cameraRec.x = camera.target.x - camera.offset.x / camera.zoom;
    cameraRec.y = camera.target.y - camera.offset.y / camera.zoom;
    cameraRec.width  = GetScreenWidth() / camera.zoom;
    cameraRec.height = GetScreenHeight() / camera.zoom;

    camera.target = target;
    camera.offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 1.4f };
}

Rectangle GetCameraRectangle()
{
    return cameraRec;
}