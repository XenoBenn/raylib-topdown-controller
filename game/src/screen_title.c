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

#define NUM_FRAMES 2
//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

float frameHeight;

Texture2D button;

Vector2 mousePoint = {0.0f, 0.0f};

int btnState = 0;                                                 // Button state: 0 normal, 1 pushed
bool btnAction = false;                                           // Button action should be activated

Sound fxButtonDown;
Sound fxButtonUp;
Rectangle sourceRec;
Rectangle btnBounds;
Rectangle btnTextBounds;
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
    button = LoadTexture("resources/images/ui/button_smaller.png");

    // Define frame rectangle for drawing
    frameHeight = (float)button.height/NUM_FRAMES;
    sourceRec = (Rectangle){0, 0, (float)button.width, frameHeight};
    btnBounds = (Rectangle){ screenWidth/2.0f - button.width/2.0f, screenHeight/2.0f - button.height/NUM_FRAMES/2.0f, (float)button.width - 180, frameHeight };
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    // TODO: Update TITLE screen variables here!

    mousePoint = GetMousePosition();
    btnAction = false;

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
    sourceRec.y = btnState * frameHeight;

    // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER)/* || btnAction == true*/)
    {
        //finishScreen = 1;   // OPTIONS
        finishScreen = 2;   // GAMEPLAY
    }
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    // TODO: Draw TITLE screen here!
    // DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
    // Vector2 pos = { 20, 10 };
    // DrawTextEx(font, "TITLE SCREEN", pos, font.baseSize*3.0f, 4, DARKGREEN);
    // DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
    ClearBackground(BLACK);
    DrawTextureRec(button, sourceRec, (Vector2){ btnBounds.x, btnBounds.y }, WHITE); // Draw button frame
    DrawText("START", btnBounds.x + 90.0f, btnBounds.y + 12.0f, 28, RAYWHITE);       // This is absolutely not good and needs refactoring!
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    // TODO: Unload TITLE screen variables here!
    UnloadTexture(button);
    UnloadSound(fxButtonDown);
    UnloadSound(fxButtonUp);
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}
