#ifndef BUILDING_H
#define BUILDING_H


#include "../../raylib-master/src/raylib.h"
#include "../../raylib-master/src/raymath.h"
#include "screens.h"
//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------
extern Model modelBox;
extern Vector3 modelBoxPosition;
extern Vector3 latestBoxWorldPosition;
extern bool modelBoxShow;
extern bool isModelBoxPlaced;
extern Vector2 mousePosition;

//----------------------------------------------------------------------------------
// Inventory Functions Declaration
//----------------------------------------------------------------------------------

void InitBuilding();
void ToggleBuilding();
void Building();
void DrawBuilding();
void DeInitBuilding();
void UpdateMousePos();

#endif
