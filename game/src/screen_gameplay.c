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

#include "../../raylib-master/src/raygui.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

Vector3 modelStartPos = { 0.0f, 0.0f, 0.0f };

// Define the camera to look into our 3d world
Camera3D camera = {
    .position = (Vector3){ 0.0f, 25.0f, 3.0f },  // Camera position
    .target = (Vector3){0.0f, 0.0f, 0.0f },       // Camera looking at point
    .up = (Vector3){ 0.0f, 1.0f, 0.0f },          // Camera up vector (rotation towards target)
    .fovy = 55.0f,                                // Camera field-of-view Y
    .projection = CAMERA_PERSPECTIVE              // Camera mode type
};

float cameraYPosition;
float const MAX_CAMERA_Y_POS = 35.0f;
float const MIN_CAMERA_Y_POS = 15.0f;
Model model;
bool windowInventoryActive;
bool windowInventroyToggle;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------


// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    model = LoadModel("resources/models/obj/armor.obj");
    windowInventoryActive = false;
    windowInventroyToggle = false;
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

    if (IsKeyPressed(KEY_E)){
        windowInventoryActive = !windowInventoryActive;
    }

    cameraYPosition = GetMouseWheelMove();
    if (camera.position.y > 15.0f && camera.position.y < 35.0f){
        camera.position.y -= cameraYPosition * 1.5f;
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!

    BeginMode3D(camera);
        DrawModel(model, modelStartPos, 1.0f, WHITE);
        DrawGrid(100, 1.0f);
    EndMode3D();


    Vector3 cameraOffset = { 0.0f, 25.0f, 3.0f };

    // Normalize the movement vector
    Vector2 movement = { 0.0f, 0.0f };
    float rotate = 0.0f;

    if (IsKeyDown(KEY_W)) {
        movement.y -= 1.0f;
        rotate -= 180.0f;
    }
    if (IsKeyDown(KEY_S)) {
        movement.y += 1.0f;
        rotate+= 0.0f;
    }
    if (IsKeyDown(KEY_A)) {
        movement.x -= 1.0f;
        rotate -= 90.0f;
    }
    if (IsKeyDown(KEY_D)) {
        movement.x += 1.0f;
        rotate += 90.0f;
    }

    model.transform = MatrixRotateY(DEG2RAD * rotate);

    movement = Vector2Normalize(movement);

    // Update model movement based on input
    modelStartPos.x += movement.x * 0.1f;
    modelStartPos.z += movement.y * 0.1f;

    // Update the camera to the model
    camera.target = modelStartPos;
    camera.position.x = modelStartPos.x + cameraOffset.x;
    camera.position.z = modelStartPos.z + cameraOffset.z;

    // Raygui controls drawing
    if (windowInventoryActive) {
        windowInventoryActive = !GuiWindowBox((Rectangle) { 328, 152, 608, 424 }, "Inventory" );
    }
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
