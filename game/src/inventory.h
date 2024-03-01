#ifndef INVENTORY_H
#define INVENTORY_H

#include "../../raylib-master/src/raylib.h"
#include "../../raylib-master/src/raygui.h"
#include "screens.h"


//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------
extern Rectangle windowInventoryPos;
extern bool windowInventoryActive;
extern Vector2 windowAnchor;
//----------------------------------------------------------------------------------
// Inventory Functions Declaration
//----------------------------------------------------------------------------------

void InitInventory(void);
void DrawInventory(void);
void ToggleInventory(void);
void UpdateInventory(void);
void DeInitInventory(void);

#endif // End INVENTORY_H
