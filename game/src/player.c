#include "player.h"
#include "screens.h"
#include "../../raylib-master/src/raylib.h"


//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
// Player Functions Definition
//----------------------------------------------------------------------------------

void InitPlayer() {
    player = LoadModel("resources/models/obj/player.obj");
    playerStartPosition = (Vector3){ 0.0f, 0.0f, 0.0f };
    float playerRotate = 0.0f;
    float playerLastRotate = 0.0f;
    
}

void DrawPlayer() {
    DrawModel(player, playerStartPosition, 1.0f, BLUE);
}

void UpdatePlayer() {
    
}

void DeInitPlayer() {
    
}

void CameraDistance() {
    
}
