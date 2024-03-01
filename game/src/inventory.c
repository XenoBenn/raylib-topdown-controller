#include "../../raylib-master/src/raylib.h"
#include "../../raylib-master/src/raygui.h"
#include "inventory.h"
#include <stdlib.h>
#include <stdio.h>

// Max rows and cols in the inventory stash that the player can have
#define MAX_STASH_COLS 10
#define MAX_STASH_ROWS 6
//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static const int screenWidth = 1280;
static const int screenHeight = 720;

Rectangle windowInventoryPos = {96, 40, 1016, 632};
Vector2 windowAnchor = { };
Rectangle inventoryStashBar;
Rectangle inventoryItemSlot;
Rectangle inventoryItemBrowser;
Rectangle inventoryBrowserBar;
Rectangle inventoryStash;
float itemSlotOffset = 64; // The needed amount to shift the rectangles to be offsetted
Rectangle itemSlotRow[MAX_STASH_COLS];
Rectangle *itemSlot;
//----------------------------------------------------------------------------------
// Inventory Functions Definition
//----------------------------------------------------------------------------------
void InitInventory() {
    Vector2 windowAnchor = { (float)screenWidth/2.0f - windowInventoryPos.width/2.0f, (float)screenHeight/2.0f - windowInventoryPos.height/2.0f };
    windowInventoryPos = (Rectangle){ windowAnchor.x, windowAnchor.y, 1016, 632 };
    inventoryStashBar = (Rectangle){ windowAnchor.x + 8, windowAnchor.y + 32, 656, 592 };
    inventoryItemBrowser = (Rectangle){ windowAnchor.x + 672, windowAnchor.y + 32, 336, 592 };
    inventoryBrowserBar = (Rectangle){ windowAnchor.x + 680, windowAnchor.y + 40, 320, 384 };
    inventoryStash = (Rectangle){ windowAnchor.x + 16, windowAnchor.y + 40, 640, 384 };
    inventoryItemSlot = (Rectangle) { windowAnchor.x + 24, windowAnchor.y +48, 48, 48 };
}

void DrawInventory() {
    Rectangle *itemSlot = (Rectangle *)malloc(MAX_STASH_COLS * sizeof(Rectangle)); // Inventory slot array
    if (windowInventoryActive) {
        windowInventoryActive = !GuiWindowBox((Rectangle)windowInventoryPos, "Inventory");
        GuiPanel((Rectangle)inventoryStashBar, NULL); // Stash bar
        GuiPanel((Rectangle)inventoryItemBrowser, NULL); // Item bowser bar
        GuiPanel((Rectangle)inventoryBrowserBar, NULL); // Item bowser
        GuiPanel((Rectangle)inventoryStash, NULL); // Stash space
        GuiPanel((Rectangle)inventoryItemSlot, NULL); // Item slot
        for (int i = 0; i < MAX_STASH_COLS; i++) {
            itemSlot[i] = (Rectangle){ inventoryItemSlot.x + (itemSlotOffset * i), inventoryItemSlot.y, inventoryItemSlot.width, inventoryItemSlot.height };
            for (int j = 0; j < MAX_STASH_ROWS; j++) {
                itemSlot[j] = (Rectangle) { inventoryItemSlot.x, inventoryItemSlot.y + (itemSlotOffset * i), inventoryItemSlot.width, inventoryItemSlot.height };
                GuiPanel(itemSlot[i], NULL );
            }
        }
    }
}

void ToggleInventory() {
        windowInventoryActive = !windowInventoryActive;
}

void DeInitInventory() {
    free(itemSlot);
}

