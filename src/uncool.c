/*******************************************************************************************
 *
 *   uncool
 *
 ********************************************************************************************/
#define DAVLIB_IMPLEMENTATION
#include "uncool.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#include <stdio.h>

static void UpdateDrawFrame(void);
extern GameState gameState, initialState;

int main() {
  initialState = gameState;
  gameState.menu->data = &gameState;

  // Set MSAA 4X hint before windows creation
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_MAXIMIZED);
  SetTraceLogLevel(LOG_NONE);

  InitWindow(1260, 720, "Centretown - UNCOOL");
  int monitor = GetCurrentMonitor();
  SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
  SetWindowPosition(0, 0);
  gameState.background = LoadTexture("resources/background.png");
  for (int i = 0; i < 10; i++) {
    const char *fname = TextFormat("resources/%03d.png", i + 1);
    gameState.earth[i] = LoadTexture(fname);
    printf("%s\n", fname);
  }

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
  SetTargetFPS(60);            // Set our game to run at 60 frames-per-second
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    UpdateDrawFrame();
  }
#endif

  UnloadTexture(gameState.background);
  for (int i = 0; i < 10; i++) {
    UnloadTexture(gameState.earth[i]);
  }
  return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void) {
  gameState.now = GetTime();
  if (IsWindowFocused()) {
    gameState.inputMode = UpdateMode(gameState.inputMode, gameState.now);
    if (gameState.inputMode == SELECTION_MODE) {
      NavigateMenu(gameState.menu, gameState.now);
    } else {
      UpdateState(&gameState, &initialState);
    }
  }

  gameState.dest.width = (float)GetRenderWidth();
  gameState.dest.height = (float)GetRenderHeight();
  Rectangle source;
  source.x = gameState.source.x;
  source.y = gameState.source.y;
  source.width = gameState.dest.width;
  source.height = gameState.dest.height;
  BeginDrawing();

  ClearBackground(BLACK);
  // TEXTURE_WRAP_REPEAT = 0,                // Repeats texture in tiled mode
  // TEXTURE_WRAP_CLAMP,                     // Clamps texture to edge pixel in
  // tiled mode TEXTURE_WRAP_MIRROR_REPEAT,             // Mirrors and repeats
  // the texture in tiled mode TEXTURE_WRAP_MIRROR_CLAMP               //
  // Mirrors and clamps to border the texture in tiled mode
  if (gameState.now > gameState.earthRate) {
    gameState.earthRate = gameState.now + 1.0f;
    gameState.earthIndex++;
    gameState.earthIndex = CLAMPNUM(gameState.earthIndex, 0, 9);
  }

#ifndef PLATFORM_WEB
  SetTextureWrap(gameState.background, TEXTURE_WRAP_MIRROR_REPEAT);
#endif // PLATFORM_WEB
  DrawTexturePro(gameState.background, source, gameState.dest, gameState.origin,
                 gameState.rotation, WHITE);
  // DrawTexture(gameState.background, 0, 0, WHITE);
  DrawTextureEx(gameState.earth[gameState.earthIndex],
                (Vector2){.x = gameState.dest.width * .6f,
                          .y = gameState.dest.height * .1f},
                0.0f, 0.12, WHITE);

  BeginMode3D(gameState.camera);
  DrawCube(gameState.cubePosition, 1.0f, 1.0f, 1.0f, ORANGE);
  DrawCubeWires(gameState.cubePosition, 1.0f, 1.0f, 1.0f, YELLOW);
  // DrawGrid(10, 1.0f);
  EndMode3D();

  DrawFPS(10, 10);
  if (SELECTION_MODE == gameState.inputMode) {
    DrawMenu(gameState.menu, (Position){.x = 2, .y = 1});
  }
  EndDrawing();
}
