#include "raylib.h"
#include "uncool.h"
#include <inttypes.h>

Vector3 UpdateVectorFromInput(Vector3 vec, Vector3 base, float scaleKey,
                              float scaleAxis, float scaleButton) {
  vec = KeysToVector(vec, base, scaleKey);
  vec = AxesToVector(vec, scaleAxis);
  vec = ButtonsToVector(vec, base, scaleButton);
  return vec;
}

InputMode UpdateMode(InputMode mode, double now, int menuKey) {
  int button = GAMEPAD_BUTTON_MIDDLE_RIGHT;
  int cmd = InputGamepad(1, &button, now);
  if (cmd == CMD_NONE) {
    cmd = InputKeys(1, &menuKey, now);
    if (cmd == CMD_NONE) {
      return mode;
    }
  }
  mode = (mode == GAME_MODE) ? MENU_MODE : GAME_MODE;
  return mode;
}

void UpdateState(GameState *state) {
  Shape *shape = state->shapes[state->currentShape];
  switch (state->moveMode) {
  case MODE_MOVE_SHAPE: {
    Vector3 pos = shape->Position(shape);
    pos = UpdateVectorFromInput(pos, shape->home, shape->rate.x, shape->rate.y,
                                shape->rate.z);
    shape->Move(shape, pos);
    break;
  }
  case MODE_MOVE_CAMERA_POSITION:
    state->camera.position =
        UpdateVectorFromInput(state->camera.position, state->origin.position,
                              shape->rate.x, shape->rate.y, shape->rate.z);
    break;
  case MODE_MOVE_CAMERA_TARGET:
    state->camera.target =
        UpdateVectorFromInput(state->camera.target, state->origin.target,
                              shape->rate.x, shape->rate.y, shape->rate.z);
    break;
  case MODE_MOVE_CAMERA_UP:
    state->camera.up =
        UpdateVectorFromInput(state->camera.up, state->origin.up, shape->rate.x,
                              shape->rate.y, shape->rate.z);
    break;

  case MODE_MOVE_BACKGROUND: {
    // state->source = UpdateVectorFromInput(state->source,
    // initial->source, 10.0f,
    //                                       10.0f, 10.0f);
    break;
  }

  case MODE_CHANGE_FOVY:
  default:
    break;
  }
}
