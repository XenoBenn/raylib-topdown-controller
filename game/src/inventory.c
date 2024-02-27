#include "../../raylib-master/src/raylib.h"
#include "../../raylib-master/src/raygui.h"
#include "inventory.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static const int screenWidth = 1280;
static const int screenHeight = 720;

bool windowInventoryActive;
Rectangle windowInventoryPos = { 96, 40, 1016, 632 };
Vector2 windowAnchor = { };

//----------------------------------------------------------------------------------
// Inventory Functions Definition
//----------------------------------------------------------------------------------
void InitInventory() {
    bool windowInventoryActive = false;
    Vector2 windowAnchor = { (float)screenWidth/2.0f - windowInventoryPos.width/2.0f, (float)screenHeight/2.0f - windowInventoryPos.height/2.0f };
    windowInventoryPos = (Rectangle){ windowAnchor.x, windowAnchor.y, 1016, 632 };
}

void DrawInventory() {
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    if (windowInventoryActive) {
        windowInventoryActive = !GuiWindowBox((Rectangle)windowInventoryPos, "Inventory");
        GuiPanel((Rectangle){ windowAnchor.x + 8, windowAnchor.y + 32, 656, 592 }, "NULL");
        GuiPanel((Rectangle){ windowAnchor.x + 672, windowAnchor.y + 32, 336, 592 }, "NULL");
        GuiPanel((Rectangle){ windowAnchor.x + 680, windowAnchor.y + 40, 320, 384 }, "NULL");
        GuiPanel((Rectangle){ windowAnchor.x + 16, windowAnchor.y + 40, 640, 384 }, "NULL");
        GuiPanel((Rectangle){ windowAnchor.x + 24, windowAnchor.y + 48, 48, 48 }, "NULL");
    }
}

void ToggleInventory() {
    if (windowInventoryActive) {
        windowInventoryActive = !windowInventoryActive;
    }
}

