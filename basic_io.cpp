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

#include "basic_io.hpp"

// Function to convert bool to string
const char* BoolToString(bool b) 
{
    return b ? "True" : "False";
}

// Function to print an integer with optional newline
const void PrintI(int i, bool endl) 
{
    printf("%d", i);
    
    if (endl) printf("\n");
}

// Function to print a float with optional newline
const void PrintF(float f, bool endl) 
{
    printf("%f", f);
    
    if (endl) printf("\n");
}

// Function to print a string with optional newline
const void PrintS(const char* s, bool endl) 
{
    printf("%s", s);
    
    if (endl) printf("\n");
}