#include "src/menu.h"
#include "src/vec.h"
#include <inttypes.h>
#include <raylib.h>
#include <stdio.h>
#define DAVLIB_IMPLEMENTATION
#include "davlib.h"
#include "uncool.h"

inline Vector3 UpdateVectorFromInput(Vector3 vec, Vector3 base, float scaleKey,
                                     float scaleAxis, float scaleButton) {
  vec = KeysToVector(vec, base, scaleKey);
  vec = AxesToVector(vec, base, scaleAxis);
  vec = ButtonsToVector(vec, base, scaleButton);
  return vec;
}

InputMode UpdateMode(InputMode mode, double now) {
  int button = GAMEPAD_BUTTON_MIDDLE_RIGHT;
  int cmd = InputGamepad(1, &button, now);
  if (cmd == CMD_NONE) {
    int key = KEY_F2;
    cmd = InputKeys(1, &key, now);
    if (cmd == CMD_NONE) {
      return mode;
    }
  }
  mode = (mode == GAME_MODE) ? SELECTION_MODE : GAME_MODE;
  return mode;
}

AutomationEvent event;

void UpdateState(GameState *state, GameState *initial) {
  state->now = GetTime();
  if (state->now > state->earthRate) {
    state->earthRate = state->now + 1.0f;
    state->earthIndex++;
    state->earthIndex = CLAMPNUM(state->earthIndex, 0, 9);
  }

  state->inputMode = UpdateMode(state->inputMode, state->now);
  if (state->inputMode == SELECTION_MODE) {
    return;
  }

  switch (state->moveMode) {
  case MODE_MOVE_CUBE:
    state->cubePosition = UpdateVectorFromInput(
        state->cubePosition, initial->cubePosition, 0.2f, 4.0f, 0.2f);
    break;
  case MODE_MOVE_CAMERA_POSITION:
    state->camera.position = UpdateVectorFromInput(
        state->camera.position, initial->camera.position, 0.2f, 4.0f, 0.2f);
    break;
  case MODE_MOVE_CAMERA_TARGET:
    state->camera.target = UpdateVectorFromInput(
        state->camera.target, initial->camera.target, 0.2f, 4.0f, 0.2f);
    break;
  case MODE_MOVE_CAMERA_UP:
    state->camera.up = UpdateVectorFromInput(
        state->camera.up, initial->camera.up, 0.2f, 4.0f, 0.2f);
    break;

  case MODE_MOVE_BACKGROUND: {
    state->source = UpdateVectorFromInput(state->source, initial->source, 10.0f,
                                          10.0f, 1.0f);
    CLAMPNUM(0, 0, 0);
    return;
  }

  case MODE_CHANGE_FOVY:
  default:
    return;
  }
}
