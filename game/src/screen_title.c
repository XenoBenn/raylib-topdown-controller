/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Title Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "../../raylib-master/src/raylib.h"
#include "screens.h"
#include <stdbool.h>

#define RAYGUI_IMPLEMENTATION
#include "../../raylib-master/src/raygui.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;


Vector2 mousePoint = {0.0f, 0.0f};

bool btnStartAction = false;                                           // Button action should be activated

Sound fxButtonDown;
Sound fxButtonUp;

bool buttonStartPressed;
bool buttonExitPressed;
bool buttonOptionsPressed;
bool btnOptionsAction; 
//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    // TODO: Initialize TITLE screen variables here!
    framesCounter = 0;
    finishScreen = 0;

    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();
    InitAudioDevice();

    fxButtonDown = LoadSound("resources/sounds/btnDown.ogg");
    fxButtonUp = LoadSound("resources/sounds/btnUp.ogg");

    buttonStartPressed = false;
    buttonStartPressed = false;
    buttonOptionsPressed = false;
    btnOptionsAction = false;
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    // TODO: Update TITLE screen variables here!

    mousePoint = GetMousePosition();
    btnStartAction = false;

    if (buttonStartPressed) {
        PlaySound(fxButtonDown);
        btnStartAction = true;
    }

    if (buttonOptionsPressed) {
        PlaySound(fxButtonDown);
        btnOptionsAction = true;
    }

    if (buttonExitPressed) {
        PlaySound(fxButtonDown);
        CloseWindow();
    }

/* Old code with the image/rectangle collision recognition. Want to keep it here in case I will need it later
    if (CheckCollisionPointRec(mousePoint, btnBounds)){
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                PlaySound(fxButtonDown);
            }
            btnState = 1;
        } else {
            btnState = 0;
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            btnAction = true;
            PlaySound(fxButtonUp);
        }
    } else {
        btnState = 0;
    }

    if (btnAction) {
    }
*/

    // Press enter or tap to change to GAMEPLAY screen
    if (btnStartAction == true)
    {
        //finishScreen = 1;   // OPTIONS
        finishScreen = 2;   // GAMEPLAY
    }
    if (btnOptionsAction == true) {
        finishScreen = 1;   // OPTIONS
    }
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    // TODO: Draw TITLE screen here!
    ClearBackground(BLACK);

    buttonStartPressed = GuiButton((Rectangle){ 96, 96, 120, 24 }, "START");
    buttonOptionsPressed = GuiButton((Rectangle){ 96, 126, 120, 24 }, "OPTIONS");
    buttonExitPressed = GuiButton((Rectangle){ 96, 156, 120, 24 }, "EXIT");
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    // TODO: Unload TITLE screen variables here!
    UnloadSound(fxButtonDown);
    UnloadSound(fxButtonUp);
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}
