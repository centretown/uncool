
#include "davlib.h"
#include "uncool.h"
#include <assert.h>
#include <stdlib.h>

void OnChooseMode(void *menuptr, int current, int currentChoice) {
  Menu *menu = menuptr;
  assert(menu);
  assert(menu->data);
  GameState *state = menu->data;
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
    .titleColor = GREEN,
    .titleActive = ORANGE,
    .labelActive = (Color){.r = 0x00, .g = 0xb7, .b = 0x9b, .a = 0xff},
    .labelColor = (Color){.r = 0x00, .g = 0x89, .b = 0x79, .a = 0x7f},
    .valueColor = (Color){.r = 0x7b, .g = 0x4f, .b = 0x13, .a = 0x7f},
    .valueActive = YELLOW,
    .fontSize = 24,
};

static MenuItem *menuItems[] = {
    &(MenuItem){
        .label = "Current Mode",
        .choices =
            (char *[]){
                "Move Cube",
                "Move Camera Position",
                "Move Camera Target",
                "Move Camera Up",
                "Change Fovy",
                "Move Background",
            },
        .choiceCount = 6,
        .onChoose = OnChooseMode,
    },
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
};

static Menu menu = (Menu){
    .position = {.x = 1, .y = 1},
    .title = "Settings",
    .theme = &theme,
    .valueColumn = 12,
    .data = 0, // SetMenuState
    .current = 0,
    .itemCount = 2,
    .items = menuItems,
};

GameState gameState = (GameState){
    .cubePosition = (Vector3){.x = 0.0f, .y = 0.0f, .z = 0.0f},
    .camera =
        (Camera){
            .position = (Vector3){.x = 3.0f, .y = 3.0f, .z = 2.0f},
            .target = (Vector3){.x = 0.0f, .y = 0.0f, .z = 0.0f},
            .up = (Vector3){.x = 0.0f, .y = 1.0f, .z = 0.0f},
            .fovy = 60.0f,
            .projection = CAMERA_PERSPECTIVE,
        },
    .moveMode = MODE_MOVE_CUBE,
    .inputMode = GAME_MODE,
    .labelColor = YELLOW,
    .valueColor = ORANGE,
    .background = {0},
    .earth = {0},
    .earthIndex = 0,
    .source = {0},
    .dest = {0},
    .origin = (Vector2){.x = 0, .y = 0},
    .rotation = 0,
    .menu = &menu,
};

GameState initialState = {0};
