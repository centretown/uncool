#include "uncool.h"

#include <assert.h>
#include <stdlib.h>

// must be set as first statement
extern GameState gameState;

// OnChoose Handler Macros
#define MENU_ITEM_CHOICE(menuptr)                                              \
  assert(menuptr);                                                             \
  Menu *menu = menuptr;                                                        \
  MenuItem *item = menu->items[menu->current];                                 \
  int choiceCurrent = item->choiceCurrent;

#define MENU_ITEM_FLOAT(menuptr)                                               \
  assert(menuptr);                                                             \
  Menu *menu = menuptr;                                                        \
  MenuItem *item = menu->items[menu->current];                                 \
  float value = item->fvalue;

#define MENU_ITEM_INT(menuptr)                                                 \
  assert(menuptr);                                                             \
  Menu *menu = menuptr;                                                        \
  assert(menu);                                                                \
  MenuItem *item = menu->items[menu->current];                                 \
  int value = item->ivalue;

#define GAME_STATE(menuptr)                                                    \
  Menu *menu = menuptr;                                                        \
  assert(menu);                                                                \
  MenuItem *item = menu->items[menu->current];                                 \
  int choiceCurrent = item->choiceCurrent;

#define GAME_STATE_INT(menuptr)                                                \
  Menu *menu = menuptr;                                                        \
  assert(menu);                                                                \
  MenuItem *item = menu->items[menu->current];                                 \
  int value = item->ivalue;

#define SET_COLOR_ITEMS(menuptr, c)                                            \
  Menu *menu = menuptr;                                                        \
  MenuItem **items = menu->items;                                              \
  Color *color = c;                                                            \
  menu->data = color;                                                          \
  items[0]->ivalue = color->r;                                                 \
  items[1]->ivalue = color->g;                                                 \
  items[2]->ivalue = color->b;                                                 \
  items[3]->ivalue = color->a;

// Handlers

void OnSetColorRed(Menu *menuptr) {
  GAME_STATE_INT(menuptr);
  Color *color = menu->data;
  color->r = value;
}
void OnSetColorGreen(Menu *menuptr) {
  GAME_STATE_INT(menuptr);
  Color *color = menu->data;
  color->g = value;
}
void OnSetColorBlue(Menu *menuptr) {
  GAME_STATE_INT(menuptr);
  Color *color = menu->data;
  color->b = value;
}
void OnSetColorAlpha(Menu *menuptr) {
  GAME_STATE_INT(menuptr);
  Color *color = menu->data;
  color->a = value;
}

void OnChooseShape(Menu *menuptr) {
  MENU_ITEM_CHOICE(menuptr);
  gameState.currentShape = choiceCurrent;
}

void OnChooseMode(Menu *menuptr) {
  GAME_STATE(menuptr);
  gameState.moveMode = choiceCurrent;
}

void OnChooseFont(Menu *menuptr) {
  GAME_STATE(menuptr);
  gameState.theme->fontSize = atoi(item->choices[choiceCurrent]);
}

void OnPushTitleColor(Menu *menuptr) {
  SET_COLOR_ITEMS(menuptr, &gameState.theme->titleColor);
}
void OnPushTitleActive(Menu *menuptr) {
  SET_COLOR_ITEMS(menuptr, &gameState.theme->titleActive);
}
void OnPushTitleHover(Menu *menuptr) {
  SET_COLOR_ITEMS(menuptr, &gameState.theme->titleHover);
}
void OnPushLabelColor(Menu *menuptr) {
  SET_COLOR_ITEMS(menuptr, &gameState.theme->labelColor);
}
void OnPushLabelActive(Menu *menuptr) {
  SET_COLOR_ITEMS(menuptr, &gameState.theme->labelActive);
}
void OnPushLabelHover(Menu *menuptr) {
  SET_COLOR_ITEMS(menuptr, &gameState.theme->labelHover);
}
void OnPushValueColor(Menu *menuptr) {
  SET_COLOR_ITEMS(menuptr, &gameState.theme->valueColor);
}
void OnPushValueActive(Menu *menuptr) {
  SET_COLOR_ITEMS(menuptr, &gameState.theme->valueActive);
}
void OnPushValueHover(Menu *menuptr) {
  SET_COLOR_ITEMS(menuptr, &gameState.theme->valueHover);
}
void OnPushBackgroundColor(Menu *menuptr) {
  SET_COLOR_ITEMS(menuptr, &gameState.theme->backgroundColor);
}
void OnPushColorDim(Menu *menuptr) {
  SET_COLOR_ITEMS(menuptr, &gameState.theme->colorDim);
}
void OnPushColorHover(Menu *menuptr) {
  SET_COLOR_ITEMS(menuptr, &gameState.theme->colorHover);
}
