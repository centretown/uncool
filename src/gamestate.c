
#include "davlib.h"
#include "raylib.h"
#include "uncool.h"

static MenuItem *menuItems[] = {
    &(MenuItem){
        .itemType = MENU_SUB, .label = "Theme",
        // .menu = themeMenu,
    },
    &(MenuItem){
        .itemType = MENU_CHOICE,
        .label = "Select Shape",
        .choices =
            (char *[]){
                "Mesh Poly",
                "Mesh Plane",
                "Mesh Cube",
                "Mesh Sphere",
                "Mesh Hemisphere",
                "Mesh Cylinder",
                "Mesh Cone",
                "Mesh Torus",
                "Mesh Knot",
                "Cube",
                "Sphere",
                "Capsule",
                "Cylinder",
            },
        .choiceCount = 12,
        .onChoose = OnChooseShape,
    },
    &(MenuItem){
        .itemType = MENU_CHOICE,
        .label = "Current Mode",
        .choices =
            (char *[]){
                "Move Object",
                "Move Camera Position",
                "Move Camera Target",
                "Move Camera Up",
                "Change Fovy",
                "Move Background",
            },
        .choiceCount = 6,
        .onChoose = OnChooseMode,
    },
};

Menu menu = (Menu){
    .title = "Settings",
    .current = 0,
    .itemCount = sizeof(menuItems) / sizeof(menuItems[0]),
    .items = menuItems,
};

#include "shapes.c"

const Camera cameraOrigin = (Camera){
    .position = (Vector3){.x = 3.0f, .y = 3.0f, .z = 2.0f},
    .target = (Vector3){.x = 0.0f, .y = 0.0f, .z = 0.0f},
    .up = (Vector3){.x = 0.0f, .y = 1.0f, .z = 0.0f},
    .fovy = 60.0f,
    .projection = CAMERA_PERSPECTIVE,
};

GameState gameState = (GameState){
    .camera = cameraOrigin,
    .origin = cameraOrigin,
    .moveMode = MODE_MOVE_SHAPE,
    .inputMode = GAME_MODE,
    .labelColor = YELLOW,
    .valueColor = ORANGE,
    .menuPos = (Rectangle){.x = 5, .y = 2, .width = 16.0f, .height = 16.0f},
    .menu = &menu,
    .shapes = gameShapes,
    .currentShape = 0,
    .shapeCount = sizeof(gameShapes) / sizeof(gameShapes[0]),
};
