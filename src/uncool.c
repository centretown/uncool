/*******************************************************************************************
 *
 *   uncool
 *
 ********************************************************************************************/
#include <stdio.h>
#define DAVLIB_IMPLEMENTATION
#include "uncool.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static void UpdateDrawFrame(void);

// in gamestate.c
extern GameState gameState, initialState;

int main() {
  gameState.menu->custom = &gameState;
  InitShapes(gameState.shapeCount, gameState.shapes);
  initialState = gameState;

  // Set MSAA 4X hint before windows creation
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_MAXIMIZED);
  SetTraceLogLevel(LOG_NONE);

  InitWindow(1260, 720, "Centretown - UNCOOL");
  int monitor = GetCurrentMonitor();
  SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
  SetWindowPosition(0, 0);

  // load resources
  gameState.background = LoadTexture("resources/background.png");
  for (int i = 0; i < 10; i++) {
    const char *fname = TextFormat("resources/%03d.png", i + 1);
    gameState.earth->tex[i] = LoadTexture(fname);
    printf("%s\n", fname);
  }

  Image image = LoadImage("texture.png");
  gameState.projection = LoadTextureFromImage(image);

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
  UnloadTexture(gameState.projection);
  for (int i = 0; i < 10; i++) {
    UnloadTexture(gameState.earth->tex[i]);
  }
  return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void) {
  gameState.now = GetTime();
  if (IsWindowFocused()) {
    gameState.inputMode = UpdateMode(gameState.inputMode, gameState.now);
    if (gameState.inputMode == MENU_MODE) {
      NavigateMenu(gameState.menu, gameState.now);
    } else { // GAME_MODE
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
  Earth *earth = gameState.earth;
  if (gameState.now > earth->rate) {
    earth->rate = gameState.now + 1.0f;
    earth->current++;
    earth->current = CLAMPNUM(earth->current, 0, 9);
  }

#ifndef PLATFORM_WEB
  SetTextureWrap(gameState.background, TEXTURE_WRAP_MIRROR_REPEAT);
#endif // PLATFORM_WEB
  DrawTexturePro(gameState.background, source, gameState.dest, gameState.origin,
                 gameState.rotation, WHITE);
  // DrawTexture(gameState.background, 0, 0, WHITE);
  DrawTextureEx(earth->tex[earth->current],
                (Vector2){.x = gameState.dest.width * .6f,
                          .y = gameState.dest.height * .1f},
                0.0f, 0.12, WHITE);

  BeginMode3D(gameState.camera);
  // DrawGrid(10, 1.0f);
  // DrawShapes(gameState.shapeCount, gameState.shapes);
  for (int i = 0; i < gameState.shapeCount; i++) {
    if (i == gameState.currentShape) {
      Shape *shape = gameState.shapes[i];
      shape->Draw(shape);
      break;
    }
  }
  EndMode3D();

  DrawFPS(10, 10);
  if (MENU_MODE == gameState.inputMode) {
    DrawMenu(gameState.menu, (Position){.x = 2, .y = 1});
  }
  EndDrawing();
}
