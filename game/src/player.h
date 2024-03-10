#ifndef PLAYER_H
#define PLAYER_H

#include "../../raylib-master/src/raylib.h"
#include "screens.h"


//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
extern Model player;
extern Model character;
extern Vector3 playerStartPosition;
extern float playerRotate;
extern float playerLastRotate;
extern float cameraHeight;
extern float const MAX_CAMERA_HEIGHT;
extern float const MIN_CAMERA_HEIGHT;



//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Inventory Functions Declaration
//----------------------------------------------------------------------------------

void InitPlayer(void);
void DrawPlayer(void);
void CameraDistance(void);
void UpdatePlayer(void);
void DeInitPlayer(void);

#endif // End INVENTORY_H
