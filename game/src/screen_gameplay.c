/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
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
#include "../../raylib-master/src/raymath.h"
#include "screens.h"

#include <stdio.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

Model model;

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    model = LoadModel("resources/models/obj/armor.obj");
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER))
    {
        finishScreen = 1;
    }
}

    Vector3 modelStartPos = { 0.0f, 0.0f, 0.0f };

    // Define the camera to look into our 3d world
    Camera3D camera = {

    .position = (Vector3){ 0.0f, 10.0f, 10.0f },  // Camera position
    .target = (Vector3){0.0f, 0.0f, 0.0f },       // Camera looking at point
    .up = (Vector3){ 0.0f, 1.0f, 0.0f },          // Camera up vector (rotation towards target)
    .fovy = 45.0f,                                // Camera field-of-view Y
    .projection = CAMERA_PERSPECTIVE              // Camera mode type
};


// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!

    BeginMode3D(camera);
        DrawModel(model, modelStartPos, 1.0f, WHITE);
        DrawGrid(10, 1.0f);
    EndMode3D();

    camera.target = modelStartPos;

    if (IsKeyDown(KEY_W)) {
        modelStartPos.z -= 0.1f;
}
    if (IsKeyDown(KEY_S)) {
        modelStartPos.z += 0.1f;
}
    if (IsKeyDown(KEY_A)) {
        modelStartPos.x -= 0.1f;
}
    if (IsKeyDown(KEY_D)) {
        modelStartPos.x += 0.1f;
}
    UpdateCamera(&camera, CAMERA_THIRD_PERSON );
    Vector3 cameraOffset = { 0.0f, 10.0f, 10.0f };
    camera.position.x = modelStartPos.x + cameraOffset.x;
    camera.position.z = modelStartPos.z + cameraOffset.z;
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    UnloadModel(model);
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}
