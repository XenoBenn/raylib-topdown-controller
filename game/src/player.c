#include "player.h"
#include "screens.h"
#include "../../raylib-master/src/raylib.h"
#include "../../raylib-master/src/raymath.h"
#include <math.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------

float const MAX_CAMERA_HEIGHT = 35.0f;
float const MIN_CAMERA_HEIGHT = 15.0f;
float cameraHeight;
Model player;
Model character;
Vector3 playerStartPosition = {0};
Vector3 characterPosition = {0};
float playerRotate = 0.0f;
float playerLastRotate = 0.0f;


    int animsCount = 0;
    unsigned int animIndex = 0;
    unsigned int animCurrentFrame = 0;
    ModelAnimation *modelAnimations;
//----------------------------------------------------------------------------------
// Player Functions Definition
//----------------------------------------------------------------------------------

void InitPlayer() {
    player = LoadModel("resources/models/obj/player.obj");
    character = LoadModel("resourves/models/glb/idle.glb");

    int animsCount = 0;
    unsigned int animIndex = 0;
    unsigned int animCurrentFrame = 0;
    ModelAnimation *modelAnimations = LoadModelAnimations("resources/models/glb/idle.glb", &animsCount);
    Vector3 characterPosition = { 0.0f, 0.0f, 0.0f };

    playerStartPosition = (Vector3){ 0.0f, 0.0f, 0.0f };
    float playerRotate = 0.0f;
    float playerLastRotate = 0.0f;
    
}

void DrawPlayer() {
    DrawModel(player, playerStartPosition, 1.0f, RED);
    DrawModel(character, characterPosition, 1.0f, WHITE);
}

void UpdatePlayer() {

    ModelAnimation anim = modelAnimations[animIndex];
    animCurrentFrame = (animCurrentFrame + 1) % anim.frameCount;
    UpdateModelAnimation(character, anim, animCurrentFrame);


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
        playerRotate = atan2(movement.x, movement.y) * RAD2DEG;
        playerLastRotate = playerRotate;
    }

    playerRotate = playerLastRotate;
    player.transform = MatrixRotateY(DEG2RAD * playerRotate);

    movement = Vector2Normalize(movement);

    // Update model movement based on input
    playerStartPosition.x += movement.x * 0.1f;
    playerStartPosition.z += movement.y * 0.1f;

    // Update the camera to the model
    camera.target = playerStartPosition;
    camera.position.x = playerStartPosition.x + cameraOffset.x;
    camera.position.z = playerStartPosition.z + cameraOffset.z;
    
}

void DeInitPlayer() {
    UnloadModel(player);
}

void CameraDistance() {
    cameraHeight = GetMouseWheelMove();
    camera.position.y -= cameraHeight * 2.0f;

    // Check if the camera position exceeds the limits and adjust if neccessary
    if (camera.position.y <= MIN_CAMERA_HEIGHT) {
        camera.position.y = MIN_CAMERA_HEIGHT;
    } else if (camera.position.y >= MAX_CAMERA_HEIGHT) {
        camera.position.y = MAX_CAMERA_HEIGHT;
    } 
}
