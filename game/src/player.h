#ifndef PLAYER_H
#define PLAYER_H

#include "../../raylib-master/src/raylib.h"
#include "screens.h"


//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Inventory Functions Declaration
//----------------------------------------------------------------------------------

void InitPlayer(void);
void DrawPlayer(void);
void UpdatePlayer(void);
void DeInitPlayer(void);

#endif // End INVENTORY_H
