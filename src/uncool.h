#ifndef UNCOOL_DEFINED
#define UNCOOL_DEFINED

#include "davlib.h"
#include "raylib.h"
typedef enum MoveMode {
  MODE_MOVE_SHAPE,
  MODE_MOVE_CAMERA_POSITION,
  MODE_MOVE_CAMERA_TARGET,
  MODE_MOVE_CAMERA_UP,
  MODE_CHANGE_FOVY,
  MODE_MOVE_BACKGROUND,
  MODE_MOVE_BEGIN = MODE_MOVE_SHAPE,
  MODE_MOVE_END = MODE_MOVE_CAMERA_UP,
} MoveMode;

typedef enum InputMode {
  GAME_MODE, // fast action
  MENU_MODE, // controlled input
} InputMode;

typedef struct Earth {
  Texture2D tex[10];
  int current;
  int count;
  double rate;
  Rectangle dest;
} Earth;

typedef struct GameState {
  Camera origin;
  Camera camera;
  InputMode inputMode;
  MoveMode moveMode;
  Color labelColor;
  Color valueColor;
  Vector2 buttonSize;

  // Earth *earth;
  double now;
  Theme *theme;
  Texture2D background;
  Texture2D projection;
  Material material;
  Rectangle menuPos;
  Menu *menu;

  int currentShape;
  int shapeCount;
  Shape **shapes;
} GameState;

typedef enum {
  CMD_UNDEFINED = -1,
  CMD_MOVE_X = 0,
  CMD_MOVE_Y,
  CMD_MOVE_Z,
  CMD_MOVE_HOME,
  CMD_MOVE_COUNT,
} CmdID;

void UpdateState(GameState *state);
const char *ModeTitle(MoveMode mode);
void DrawSettingsMenu(double now);
void SetMenuState(GameState *state);
InputMode UpdateMode(InputMode mode, double now, int menuKey);

// Handlers

void OnChooseMode(Menu *menuptr);
void OnChooseShape(Menu *menuptr);
#endif // UNCOOL_DEFINED
