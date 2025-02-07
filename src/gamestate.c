
#include "davlib.h"
#include "raylib.h"
#include "uncool.h"
#include <assert.h>
#include <stdlib.h>

// Handler Macros

#define MENU_ITEM_CHOICE(menuptr)                                              \
  Menu *menu = menuptr;                                                        \
  assert(menu);                                                                \
  assert(menu->custom);                                                        \
  MenuItem *item = menu->items[menu->current];                                 \
  int choiceCurrent = item->choiceCurrent;

#define MENU_ITEM_FLOAT(menuptr)                                               \
  Menu *menu = menuptr;                                                        \
  assert(menu);                                                                \
  assert(menu->custom);                                                        \
  MenuItem *item = menu->items[menu->current];                                 \
  float value = item->fvalue;

#define MENU_ITEM_INT(menuptr)                                                 \
  Menu *menu = menuptr;                                                        \
  assert(menu);                                                                \
  assert(menu->custom);                                                        \
  MenuItem *item = menu->items[menu->current];                                 \
  int value = item->ivalue;

#define GAME_STATE(menuptr)                                                    \
  Menu *menu = menuptr;                                                        \
  assert(menu);                                                                \
  assert(menu->custom);                                                        \
  GameState *state = menu->custom;                                             \
  MenuItem *item = menu->items[menu->current];                                 \
  int choiceCurrent = item->choiceCurrent;

#define GAME_STATE_INT(menuptr)                                                \
  Menu *menu = menuptr;                                                        \
  assert(menu);                                                                \
  assert(menu->custom);                                                        \
  GameState *state = menu->custom;                                             \
  MenuItem *item = menu->items[menu->current];                                 \
  int value = item->ivalue;

// Handlers

void OnChooseShape(void *menuptr) {
  GAME_STATE(menuptr);
  state->currentShape = choiceCurrent;
}

void OnChooseMode(void *menuptr) {
  GAME_STATE(menuptr);
  state->moveMode = choiceCurrent;
}

void OnChooseFont(void *menuptr) {
  MENU_ITEM_CHOICE(menuptr);
  const char *choice = item->choices[choiceCurrent];
  menu->theme->fontSize = atoi(choice);
}

void OnSetBackgroundColorRed(void *menuptr) {
  GAME_STATE_INT(menuptr);
  state->backgroundColor.r = value;
}

void OnSetBackgroundColorGreen(void *menuptr) {
  GAME_STATE_INT(menuptr);
  state->backgroundColor.g = value;
}

void OnSetBackgroundColorBlue(void *menuptr) {
  GAME_STATE_INT(menuptr);
  state->backgroundColor.b = value;
}

static Theme theme = (Theme){
    .backgroundColor = BLACK,
    .titleColor = (Color){.r = 0x00, .g = 0xf0, .b = 0x30, .a = 0xcf},
    .labelColor = (Color){.r = 0x00, .g = 0x89, .b = 0x79, .a = 0xcf},
    .valueColor = (Color){.r = 0x7b, .g = 0x4f, .b = 0x13, .a = 0xcf},

    .titleHover = (Color){.r = 0x00, .g = 0xf0, .b = 0x30, .a = 0xef},
    .labelHover = (Color){.r = 0x89, .g = 0x89, .b = 0x79, .a = 0xef},
    .valueHover = (Color){.r = 0x7b, .g = 0x4f, .b = 0x13, .a = 0xef},

    .titleActive = (Color){.r = 0x00, .g = 0xf0, .b = 0x30, .a = 0xff},
    .labelActive = (Color){.r = 0x00, .g = 0x89, .b = 0x79, .a = 0xff},
    .valueActive = (Color){.r = 0xcb, .g = 0x7f, .b = 0x13, .a = 0xff},

    .fontSize = 24,
};

static MenuItem *menuItems[] = {
    &(MenuItem){
        .itemType = MENU_INT,
        .label = "BG Red",
        .ivalue = 0,
        .imin = 0,
        .imax = 256,
        .iinc = 4,
        .onChoose = OnSetBackgroundColorRed,
    },
    &(MenuItem){
        .itemType = MENU_INT,
        .label = "BG Green",
        .ivalue = 0,
        .imin = 0,
        .imax = 256,
        .iinc = 4,
        .onChoose = OnSetBackgroundColorGreen,
    },
    &(MenuItem){
        .itemType = MENU_INT,
        .label = "BG Blue",
        .ivalue = 0,
        .imin = 0,
        .imax = 256,
        .iinc = 4,
        .onChoose = OnSetBackgroundColorBlue,
    },
    &(MenuItem){
        .itemType = MENU_CHOICE,
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
                "Red Cube",
                "Blue Sphere",
                "Green Capsule",
                "Yellow Cylinder",
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
    .menu = &menu,
    .shapes = gameShapes,
    .currentShape = 0,
    .shapeCount = sizeof(gameShapes) / sizeof(gameShapes[0]),
};

GameState initialState = {0};
