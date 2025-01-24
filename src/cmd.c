
#define DAV_LIB_IMPLEMENTATION
#include "/home/dave/src/davlib/davlib.h"

#include "uncool.h"
#include <assert.h>

const int buttonMove[] = {
    GAMEPAD_BUTTON_LEFT_FACE_LEFT, GAMEPAD_BUTTON_LEFT_FACE_RIGHT,
    GAMEPAD_BUTTON_LEFT_FACE_UP,   GAMEPAD_BUTTON_LEFT_FACE_DOWN,
    GAMEPAD_BUTTON_LEFT_TRIGGER_1, GAMEPAD_BUTTON_RIGHT_TRIGGER_1,
    GAMEPAD_BUTTON_MIDDLE_RIGHT};
const int buttonMoveCount = sizeof(buttonMove) / sizeof(buttonMove[0]);

const int keyboardMove[] = {KEY_LEFT,    KEY_RIGHT,     KEY_UP,  KEY_DOWN,
                            KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_HOME};
const int keyboardMoveCount = sizeof(keyboardMove) / sizeof(keyboardMove[0]);

const int axisMove[] = {GAMEPAD_AXIS_RIGHT_X, GAMEPAD_AXIS_LEFT_Y,
                        GAMEPAD_AXIS_RIGHT_Y, GAMEPAD_AXIS_LEFT_TRIGGER,
                        GAMEPAD_AXIS_RIGHT_TRIGGER};
const int axisMoveCount = sizeof(axisMove) / sizeof(axisMove[0]);

void UpdateState(GameState *state) {
  CmdID cmd = CMD_UNDEFINED;
  float value = 0.0f;
  int command = -1;

  PadButtonResult btr = CheckAllGamePadButtons(buttonMoveCount, buttonMove);

  if (btr.command >= 0) {
    command = btr.command;
  } else {
    command = CheckKeyboard(keyboardMoveCount, keyboardMove);
  }

  if (command >= 0) {
    switch (command) {
    case 0:
      cmd = CMD_MOVE_X;
      value = -.1;
      break;
    case 1:
      cmd = CMD_MOVE_X;
      value = .1;
      break;
    case 2:
      cmd = CMD_MOVE_Z;
      value = -.1;
      break;
    case 3:
      cmd = CMD_MOVE_Z;
      value = .1;
      break;
    case 4:
      cmd = CMD_MOVE_Y;
      value = -.1;
      break;
    case 5:
      cmd = CMD_MOVE_Y;
      value = .1;
      break;
    case 6:
      cmd = CMD_MOVE_HOME;
      value = 0;
      break;
    default:
      assert(0);
    }
    UpdateCubePosition(&state->cubePosition, cmd, value, false);
    return;
  }

  PadAxisResult axr = CheckGamePadAxes(axisMoveCount, axisMove);
  if (axr.command >= 0) {
    UpdateCubePosition(&state->cubePosition, axr.command, axr.value * 4, true);
  }

  return;
}

void UpdateCubePosition(Vector3 *pCubePosition, int cmd, float value,
                               bool absolute) {
  switch (cmd) {
  case CMD_MOVE_X:
    pCubePosition->x = (absolute) ? value : pCubePosition->x + value;
    break;
  case CMD_MOVE_Y:
    pCubePosition->y = (absolute) ? value : pCubePosition->y + value;
    break;
  case CMD_MOVE_Z:
    pCubePosition->z = (absolute) ? value : pCubePosition->z + value;
    break;
  case CMD_MOVE_HOME:
    pCubePosition->x = 0;
    pCubePosition->y = 0;
    pCubePosition->z = 0;
    break;

  default:
    break;
  }
}
