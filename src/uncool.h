#include <raylib.h>

typedef struct {
  Camera camera;
  Vector3 cubePosition;
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
void UpdateCubePosition(Vector3 *pCubePosition, int cmd, float value,
                        bool absolute);
