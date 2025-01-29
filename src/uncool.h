#ifndef UNCOOL_DEFINED
#define UNCOOL_DEFINED

#include "davlib.h"
typedef enum MoveMode {
  MODE_MOVE_CUBE,
  MODE_MOVE_CAMERA_POSITION,
  MODE_MOVE_CAMERA_TARGET,
  MODE_MOVE_CAMERA_UP,
  MODE_CHANGE_FOVY,
  MODE_MOVE_BACKGROUND,
  MODE_MOVE_BEGIN = MODE_MOVE_CUBE,
  MODE_MOVE_END = MODE_MOVE_CAMERA_UP,
} MoveMode;

typedef enum InputMode {
  GAME_MODE,      // fast action
  SELECTION_MODE, // controlled input
} InputMode;

typedef struct GameState {
  Camera camera;
  Vector3 cubePosition;
  InputMode inputMode;
  MoveMode moveMode;
  Color labelColor;
  Color valueColor;
  Texture2D background;
  Texture2D earth[10];
  int earthIndex;
  int earthCount;
  Rectangle earthdest;
  double earthRate;
  double now;
  Vector3 source;
  Rectangle dest;
  Vector2 origin;
  float rotation;
  Menu *menu;
} GameState;

typedef enum {
  CMD_UNDEFINED = -1,
  CMD_MOVE_X = 0,
  CMD_MOVE_Y,
  CMD_MOVE_Z,
  CMD_MOVE_HOME,
  CMD_MOVE_COUNT,
} CmdID;

void UpdateState(GameState *state, GameState *initial);
const char *ModeTitle(MoveMode mode);
void DrawSettingsMenu(double now);
void SetMenuState(GameState *state);
InputMode UpdateMode(InputMode mode, double now);

#endif // UNCOOL_DEFINED
