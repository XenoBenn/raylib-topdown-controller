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
#include "building.h"
#include "inventory.h"
#include "player.h"
#include "screens.h"

#include "../../raylib-master/src/raygui.h"
#define RLIGHTS_IMPLEMENTATION
#include "../../raylib-master/src/rlgl.h"

#include <math.h>
#include <stdio.h>

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

float screenHeight;
float screenWidth;
float cameraYPosition;
float const MAX_CAMERA_Y_POS = 35.0f;
float const MIN_CAMERA_Y_POS = 15.0f;
float rotate = 0.0f;
float lastRotate = 0.0f;
Model model;

bool windowInventoryActive = false;
bool modelBoxShow = false;
bool isModelPlaced = false;
//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;

    screenHeight = GetScreenHeight();
    screenWidth = GetScreenWidth();

    model = LoadModel("resources/models/obj/player.obj");
    InitPlayer();
    InitInventory();
    InitBuilding();
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
        ToggleInventory();
    }

    if (IsKeyPressed(KEY_Q)) {
        ToggleBuilding();
    }

    cameraYPosition = GetMouseWheelMove();
    // Move the camera Y position
    camera.position.y -= cameraYPosition * 2.0f;

    // Check if the camera position exceeds the limits and adjust if neccessary
    if (camera.position.y <= MIN_CAMERA_Y_POS) {
        camera.position.y = MIN_CAMERA_Y_POS;
    } else if (camera.position.y >= MAX_CAMERA_Y_POS) {
        camera.position.y = MAX_CAMERA_Y_POS;
    } 
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!


    BeginMode3D(camera);
        // Draw Player
        DrawPlayer();
        DrawModel(model, modelStartPos, 1.0f, WHITE); 

        if (modelBoxShow) {
            DrawBuilding();
        }

        DrawGrid(100, 1.0f);
    

    EndMode3D();


    Vector3 cameraOffset = { 0.0f, 25.0f, 3.0f };

    // Normalize the movement vector
    Vector2 movement = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_W)) {
        movement.y -= 1.0f;
    }
    if (IsKeyDown(KEY_S)) {
        movement.y += 1.0f;
    }
    if (IsKeyDown(KEY_A)) {
        movement.x -= 1.0f;
    }
    if (IsKeyDown(KEY_D)) {
        movement.x += 1.0f;
    }

    if (movement.x != 0 || movement.y != 0) {
        rotate = atan2(movement.x, movement.y) * RAD2DEG;
        lastRotate = rotate;
    }

    rotate = lastRotate;
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
    DrawInventory();
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    UnloadModel(model);
    DeInitInventory();
    DeInitBuilding();
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}
