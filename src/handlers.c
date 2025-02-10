#include "uncool.h"

// must be set as first statement
extern GameState gameState;

void OnChooseShape(Menu *menuptr) {
  MENU_ITEM_CHOICE(menuptr);
  gameState.currentShape = choiceCurrent;
}

void OnChooseMode(Menu *menuptr) {
  MENU_ITEM_CHOICE(menuptr);
  gameState.moveMode = choiceCurrent;
}
