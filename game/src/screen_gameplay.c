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
#include "inventory.h"
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
Model mBox;
Vector3 workBenchPosition;
Vector3 latestWorldPosition;

bool windowInventoryActive = false;
bool showCube = false;
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
    mBox = LoadModel("resources/models/obj/box.obj");
    InitInventory();
    workBenchPosition = (Vector3){ 0, 0, 0 };
    
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
        DrawModel(model, modelStartPos, 1.0f, WHITE);
    
        // Model drawing based on the toggle key of Q
        if (IsKeyPressed(KEY_Q)) {
            showCube = !showCube;
        }
        if (showCube){
            // Get the mouse position for the ray
            Vector2 mousePos = GetMousePosition();

            // Get a ray from the mouse
            Ray ray = GetMouseRay( mousePos, camera);
            // Ray from mouse to intersection of the plane
            RayCollision collision = GetRayCollisionQuad
                (ray, 
                (Vector3){-50.0, 0.0, -50.0}, 
                (Vector3){-50.0, 0.0, 50.0}, 
                (Vector3){50.0, 0.0, 50.0}, 
                (Vector3){50.0, 0.0, -50.0});

            // if the collision hits, than that is the point of the model
            if (collision.hit) {
                Vector3 intersectionPoint = collision.point;
                workBenchPosition = collision.point;
                // Draw the model on the mouse position
                DrawModelWires(mBox, (Vector3){(int)workBenchPosition.x, (int)workBenchPosition.y, (int)workBenchPosition.z}, 1.0f, LIGHTGRAY);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    isModelPlaced = true;
                    latestWorldPosition = workBenchPosition;
                }
            } 
        }
            if (isModelPlaced) {
                DrawModel(mBox, (Vector3){(int)latestWorldPosition.x, (int)latestWorldPosition.y, (int)latestWorldPosition.z}, 1.0f, RED);
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
    UnloadModel(mBox);
    DeInitInventory();
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}
