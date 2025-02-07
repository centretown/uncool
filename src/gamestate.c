
#include "davlib.h"
#include "raylib.h"
#include "uncool.h"
#include <assert.h>
#include <stdlib.h>

#define GAME_STATE(mp) ((GameState *)(((Menu *)(mp)->custom)))

// Handlers

inline static GameState *GetGameState(void *menuptr) {
  Menu *menu = menuptr;
  assert(menu);
  assert(menu->custom);
  return menu->custom;
}

void OnChooseShape(void *menuptr, int current, int currentChoice) {
  GameState *state = GetGameState(menuptr);
  state->currentShape = currentChoice;
}

void OnChooseMode(void *menuptr, int current, int currentChoice) {
  GameState *state = GetGameState(menuptr);
  state->moveMode = currentChoice;
}

void OnChooseFont(void *menuptr, int current, int currentChoice) {
  Menu *menu = menuptr;
  assert(menu);
  MenuItem *item = menu->items[current];
  const char *choice = item->choices[currentChoice];
  menu->theme->fontSize = atoi(choice);
}

static Theme theme = (Theme){
    .backgroundColor = BLACK,
    .titleColor = (Color){.r = 0x00, .g = 0xf0, .b = 0x30, .a = 0x7f},
    .labelColor = (Color){.r = 0x00, .g = 0x89, .b = 0x79, .a = 0x7f},
    .valueColor = (Color){.r = 0x7b, .g = 0x4f, .b = 0x13, .a = 0x7f},

    .titleHover = (Color){.r = 0x00, .g = 0xf0, .b = 0x30, .a = 0xcf},
    .labelHover = (Color){.r = 0x89, .g = 0x89, .b = 0x79, .a = 0xcf},
    .valueHover = (Color){.r = 0x7b, .g = 0x4f, .b = 0x13, .a = 0xcf},

    .titleActive = (Color){.r = 0x00, .g = 0xf0, .b = 0x30, .a = 0xff},
    .labelActive = (Color){.r = 0x00, .g = 0x89, .b = 0x79, .a = 0xff},
    .valueActive = (Color){.r = 0xcb, .g = 0x7f, .b = 0x13, .a = 0xff},

    .fontSize = 24,
};

static MenuItem *menuItems[] = {
    &(MenuItem){
        .label = "Font Size",
        .choices =
            (char *[]){
                "24",
                "32",
                "40",
                "48",
                "56",
                "18",
            },
        .choiceCount = 6,
        .onChoose = OnChooseFont,
    },
    &(MenuItem){
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
                "Red Cube",
                "Blue Sphere",
                "Green Capsule",
                "Yellow Cylinder",
            },
        .choiceCount = 12,
        .onChoose = OnChooseShape,
    },
    &(MenuItem){
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
    .position = {.x = 1, .y = 1},
    .title = "Settings",
    .theme = &theme,
    .valueColumn = 12,
    .current = 0,
    .itemCount = sizeof(menuItems) / sizeof(menuItems[0]),
    .items = menuItems,
    .custom = 0, // gamestate passed to handlers
    .colorDim = (Color){.a = 96, .r = 96, .g = 255, .b = 255},
    .colorHover = (Color){.a = 255, .r = 96, .g = 255, .b = 255},
};

#include "shapes.c"

GameState gameState = (GameState){
    .camera =
        (Camera){
            .position = (Vector3){.x = 3.0f, .y = 3.0f, .z = 2.0f},
            .target = (Vector3){.x = 0.0f, .y = 0.0f, .z = 0.0f},
            .up = (Vector3){.x = 0.0f, .y = 1.0f, .z = 0.0f},
            .fovy = 60.0f,
            .projection = CAMERA_PERSPECTIVE,
        },
    .moveMode = MODE_MOVE_SHAPE,
    .inputMode = GAME_MODE,
    .labelColor = YELLOW,
    .valueColor = ORANGE,
    .background = {0},
    .earth = &(Earth){0},
    .source = {0},
    .dest = {0},
    .origin = (Vector2){.x = 0, .y = 0},
    .rotation = 0,
    .menu = &menu,
    .shapes = gameShapes,
    .currentShape = 0,
    .shapeCount = sizeof(gameShapes) / sizeof(gameShapes[0]),
};

GameState initialState = {0};
