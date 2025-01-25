#include <raylib.h>
#define DAV_LIB_IMPLEMENTATION
#include "davlib.h"
#include "uncool.h"

void UpdateState(GameState *state) {
  Vector3 vec = state->cubePosition;
  vec = KeysToVector(vec, 1.0);
  vec = AxesToVector(vec, 4.0);
  vec = ButtonsToVector(vec, 1.0);
  state->cubePosition = vec;
}
