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

#include "wilgui.hpp"

CheckBox CreateCheckBox()
{
    CheckBox checkBox;
    checkBox.flag = true;
    
    return checkBox; 
}

bool DrawCheckBox(CheckBox* target, const char* text, Vector2 position, float size)
{
    Rectangle recBox = { position.x, position.y, size, size };

    Vector2 mousePosition = GetMousePosition();
    bool isMouseOver = CheckCollisionPointRec(mousePosition, recBox);

    if (isMouseOver && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        target->flag = !target->flag;
    }

    if (target->flag)
    {
        DrawRectangleRec(recBox, GRAY);
    }

    DrawRectangleLinesEx(recBox, 3, BLACK);

    const int fontSize = size / 3;

    DrawText(text, position.x + 30, position.y + 10, fontSize, BLACK);
}