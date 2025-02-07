#ifndef UNCOOL_DEFINED
#define UNCOOL_DEFINED

#include "davlib.h"
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
  Camera camera;
  InputMode inputMode;
  MoveMode moveMode;
  Color labelColor;
  Color valueColor;
  Vector2 buttonSize;

  Earth *earth;
  double now;
  Vector3 source;
  Rectangle dest;
  Vector2 origin;
  float rotation;

  Texture2D menuInactivePic;
  Texture2D menuActivePic;
  Texture2D background;
  Texture2D projection;
  Material material;
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

void UpdateState(GameState *state, GameState *initial);
const char *ModeTitle(MoveMode mode);
void DrawSettingsMenu(double now);
void SetMenuState(GameState *state);
InputMode UpdateMode(InputMode mode, double now);

#endif // UNCOOL_DEFINED
