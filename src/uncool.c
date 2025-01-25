/*******************************************************************************************
 *
 *   uncool
 *
 ********************************************************************************************/
#include <raylib.h>
#include <stdio.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif
#include "uncool.h"
//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);
static GameState gameState = (GameState){
    .cubePosition = (Vector3){0.0f, 0.0f, 0.0f},
    .camera =
        (Camera){
            .position = (Vector3){3.0f, 3.0f, 2.0f},
            .target = (Vector3){0.0f, 0.0f, 0.0f},
            .up = (Vector3){0.0f, 1.0f, 0.0f},
            .fovy = 120.0f,
            .projection = CAMERA_PERSPECTIVE,
        },
};

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main() {
  // Set MSAA 4X hint before windows creation
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_MAXIMIZED);
  SetTraceLogLevel(LOG_NONE);
  // Initialization
  //--------------------------------------------------------------------------------------
  int monitor = GetCurrentMonitor();
  int width = GetMonitorWidth(monitor);
  int height = GetMonitorHeight(monitor);
  printf("monitor=%d width%d height=%d\n", monitor, width, height);

  InitWindow(width, height, "Centretown - UNCOOL");

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    UpdateDrawFrame();
  }
#endif

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void) {
  UpdateState(&gameState);
  // Update
  //----------------------------------------------------------------------------------
  // UpdateCamera(&gameState.camera, CAMERA_FIRST_PERSON);
  //----------------------------------------------------------------------------------

  // Draw
  //----------------------------------------------------------------------------------
  BeginDrawing();

  Color c = {.r = 0x10, .g = 0x10, .b = 0x10, .a = 0xff};
  ClearBackground(c);

  BeginMode3D(gameState.camera);

  DrawCube(gameState.cubePosition, 2.0f, 2.0f, 2.0f, ORANGE);
  DrawCubeWires(gameState.cubePosition, 2.0f, 2.0f, 2.0f, YELLOW);
  DrawGrid(10, 1.0f);

  EndMode3D();

  DrawText("Welcome to the uncool universe.", 10, 40, 20, DARKGRAY);
  DrawFPS(10, 10);

  EndDrawing();
  //----------------------------------------------------------------------------------
}
