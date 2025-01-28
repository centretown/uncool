
#include "uncool.h"
#include <assert.h>
#include <stdlib.h>

void OnChooseMode(void *menuptr, int current, int currentChoice) {
  Menu *menu = menuptr;
  assert(menu->data);
  GameState *state = menu->data;
  state->moveMode = currentChoice;
}

void OnChooseFont(void *menuptr, int current, int currentChoice) {
  Menu *menu = menuptr;
  assert(menu->data);
  MenuItem *item = menu->items[current];
  const char *choice = item->choices[currentChoice];
  menu->theme->fontSize = atoi(choice);
}

Menu settingsMenu = (Menu){
    .position = {.x = 1, .y = 1},
    .title = "Settings",
    .theme =
        &(Theme){
            .backgroundColor = BLACK,
            .titleColor = GREEN,
            .titleActive = ORANGE,
            .labelActive = (Color){.r = 0x00, .g = 0xb7, .b = 0x9b, .a = 0xff},
            .labelColor = (Color){.r = 0x00, .g = 0x89, .b = 0x79, .a = 0x7f},
            .valueColor = (Color){.r = 0x7b, .g = 0x4f, .b = 0x13, .a = 0x7f},
            .valueActive = YELLOW,
            .fontSize = 24,
        },
    .valueColumn = 12,
    .data = 0, // SetMenuState
    .current = 0,
    .itemCount = 2,
    .items =
        (MenuItem *[]){
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
        },
};

void DrawSettingsMenu(double now) {
  DrawMenu(&settingsMenu, (Position){.x = 2, .y = 1}, now);
}

void SetMenuState(GameState *state) { settingsMenu.data = state; }
