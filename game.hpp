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
#include "world.hpp"
#include "bullet.hpp"
#include "camera.hpp"
#include "player.hpp"
#include "random_box.hpp"
#include "random_stone.hpp"

// Define a threshold for falling below the screen
#define FALL_THRESHOLD 5000.0f

#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"

#define PHYSAC_IMPLEMENTATION
#include "extras/physac.h"

constexpr uint16_t screenWidth  = 800;
constexpr uint16_t screenHeight = 450;
