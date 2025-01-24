/*******************************************************************************************
 *
 *   uncool
 *
 ********************************************************************************************/
#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif
#include "uncool.h"
//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
GameState gameState = {0};

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);         // Update and draw one frame
//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main() {
  // Set MSAA 4X hint before windows creation
  // SetConfigFlags(FLAG_MSAA_4X_HINT|FLAG_WINDOW_MOUSE_PASSTHROUGH|FLAG_WINDOW_UNDECORATED);
  SetTraceLogLevel(LOG_NONE);
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1800;
  const int screenHeight = 900;

  InitWindow(screenWidth, screenHeight, "Centretown - UNCOOL");

  gameState = (GameState){
      .camera.position = (Vector3){3.0f, 3.0f, 2.0f},
      .camera.target = (Vector3){0.0f, 0.0f, 0.0f},
      .camera.up = (Vector3){0.0f, 1.0f, 0.0f},
      .camera.fovy = 120.0f,
      .camera.projection = CAMERA_PERSPECTIVE,
  };

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

  Color c = {.r = 0x33, .g = 0x33, .b = 0x66, .a = 0xff};
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
