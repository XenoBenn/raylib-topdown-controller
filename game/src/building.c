#include "building.h"
#include "screens.h"
#include "../../raylib-master/src/raylib.h"


//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------

Model modelBox;
Vector3 modelBoxPosition;
// bool modelBoxShow;
bool isModelBoxPlaced;
Vector2 mousePosition;
Vector3 latestBoxWorldPosition;
// Camera3D camera;

//----------------------------------------------------------------------------------
// Building Functions Definition
//----------------------------------------------------------------------------------

void InitBuilding() {
    modelBox = LoadModel("resources/models/obj/box.obj");
    modelBoxPosition = (Vector3){ 0, 0, 0 };
    modelBoxShow = false;
    isModelBoxPlaced = false;
}

void ToggleBuilding() {
    modelBoxShow = !modelBoxShow;
}

void DeInitBuilding() {
    UnloadModel(modelBox);
}

void DrawBuilding() {
    if (modelBoxShow) {
        mousePosition = GetMousePosition();
        modelBoxPosition = (Vector3){mousePosition.x, 0.0f, mousePosition.y};
        // Get a ray from the mouse
        Ray ray = GetMouseRay( mousePosition, camera);
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
                modelBoxPosition= collision.point;
                // Draw the model on the mouse position
                DrawModelWires(modelBox, (Vector3){(int)modelBoxPosition.x, (int)modelBoxPosition.y, (int)modelBoxPosition.z}, 1.0f, LIGHTGRAY);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    isModelBoxPlaced = true;
                    latestBoxWorldPosition = modelBoxPosition;
                }
            }
    }
            if (isModelBoxPlaced) {
                DrawModel(modelBox, (Vector3){(int)latestBoxWorldPosition.x, (int)latestBoxWorldPosition.y, (int)latestBoxWorldPosition.z}, 1.0f, RED);
        }
}

void UpdateMousePos() {
    mousePosition = GetMousePosition();
}
