/*******************************************************************************************
 *
 *   uncool
 *
 ********************************************************************************************/
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif
#include "uncool.h"

static Color clearColor = {.r = 0x10, .g = 0x10, .b = 0x10, .a = 0xff};

static GameState gameState = (GameState){
    .cubePosition = (Vector3){.x = 0.0f, .y = 0.0f, .z = 0.0f},
    .camera =
        (Camera){
            .position = (Vector3){.x = 3.0f, .y = 3.0f, .z = 2.0f},
            .target = (Vector3){.x = 0.0f, .y = 0.0f, .z = 0.0f},
            .up = (Vector3){.x = 0.0f, .y = 1.0f, .z = 0.0f},
            .fovy = 60.0f,
            .projection = CAMERA_PERSPECTIVE,
        },
    .moveMode = MODE_MOVE_CUBE,
    .inputMode = GAME_MODE,
    .labelColor = YELLOW,
    .valueColor = ORANGE,
    .background = {0},
    .earth = {0},
    .earthIndex = 0,
    .source = {0},
    .dest = {0},
    .origin = (Vector2){.x = 0, .y = 0},
    .rotation = 0,
};

static GameState initialState = {0};

static void UpdateDrawFrame(void);

int main() {
  initialState = gameState;
  SetMenuState(&gameState);
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
  if (IsWindowFocused()) {
    UpdateState(&gameState, &initialState);
  }

  gameState.dest.width = (float)GetRenderWidth();
  gameState.dest.height = (float)GetRenderHeight();
  Rectangle source;
  source.x = gameState.source.x;
  source.y = gameState.source.y;
  source.width = gameState.dest.width;
  source.height = gameState.dest.height;
  BeginDrawing();

  ClearBackground(clearColor);
  // TEXTURE_WRAP_REPEAT = 0,                // Repeats texture in tiled mode
  // TEXTURE_WRAP_CLAMP,                     // Clamps texture to edge pixel in
  // tiled mode TEXTURE_WRAP_MIRROR_REPEAT,             // Mirrors and repeats
  // the texture in tiled mode TEXTURE_WRAP_MIRROR_CLAMP               //
  // Mirrors and clamps to border the texture in tiled mode

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
    DrawSettingsMenu(gameState.now);
  }
  EndDrawing();
}
