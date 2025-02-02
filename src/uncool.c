// uncool
#include "raylib.h"
#include <stdio.h>
#define DAVLIB_IMPLEMENTATION
#include "uncool.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static void UpdateDrawFrame(void);

// in gamestate.c
extern GameState gameState, initialState;

static Shader shader = {0};
static int ambientLoc = 0;
static Light lights[MAX_LIGHTS] = {0};

int main() {
  gameState.menu->custom = &gameState;
  initialState = gameState;

  // Set MSAA 4X hint before windows creation
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_MAXIMIZED);
  SetTraceLogLevel(LOG_NONE);

  InitWindow(1260, 720, "Centretown - UNCOOL");
  int monitor = GetCurrentMonitor();
  SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
  SetWindowPosition(0, 0);

  // load resources
  // gameState.background = LoadTexture("resources/background.png");
  // for (int i = 0; i < 10; i++) {
  //   const char *fname = TextFormat("resources/%03d.png", i + 1);
  //   gameState.earth->tex[i] = LoadTexture(fname);
  //   printf("%s\n", fname);
  // }

  // Load basic lighting shader
  shader = LoadShader(
      TextFormat("resources/shaders/glsl%i/lighting.vs", GLSL_VERSION),
      TextFormat("resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));
  // Get some required shader locations
  shader.locs[SHADER_LOC_MATRIX_MVP] = GetShaderLocation(shader, "mvp");
  shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
  // NOTE: "matModel" location name is automatically assigned on shader loading,
  // no need to get the location again if using that uniform name
  // shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader,
  // "matModel");
  ambientLoc = GetShaderLocation(shader, "ambient");
  SetShaderValue(shader, ambientLoc, (float[4]){0.1f, 0.1f, 0.1f, 1.0f},
                 SHADER_UNIFORM_VEC4);

  // Create lights

  lights[0] = CreateLight(LIGHT_POINT, (Vector3){-2, 1, -2}, Vector3Zero(),
                          YELLOW, shader);
  lights[1] =
      CreateLight(LIGHT_POINT, (Vector3){2, 1, 2}, Vector3Zero(), RED, shader);
  lights[2] = CreateLight(LIGHT_POINT, (Vector3){-2, 1, 2}, Vector3Zero(),
                          GREEN, shader);
  lights[3] = CreateLight(LIGHT_POINT, (Vector3){2, 1, -2}, Vector3Zero(), BLUE,
                          shader);

  Image image = LoadImage("wood.jpg");
  gameState.projection = LoadTextureFromImage(image);
  Material material = LoadMaterialDefault();
  material.shader = shader; // Set shader effect to 3d model
  // texture gets bound to models
  material.maps[MATERIAL_MAP_ROUGHNESS].texture = gameState.projection;
  material.maps[MATERIAL_MAP_DIFFUSE].color =
      (Color){.r = 0, .g = 255, .b = 0, .a = 255};

  if (!IsMaterialValid(material)) {
    printf("MATERIAL INVALID\n");
  } else {
    printf("MATERIAL ok\n");
  }

  InitShapes(gameState.shapeCount, gameState.shapes, material);

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
  SetTargetFPS(60);            // Set our game to run at 60 frames-per-second
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    UpdateDrawFrame();
  }
#endif

  for (int i = 0; i < gameState.shapeCount; i++) {
    gameState.shapes[i]->Unload(gameState.shapes[i]);
  }

  UnloadShader(shader); // Unload shader
  // UnloadTexture(gameState.background);
  // UnloadTexture(gameState.projection);
  // for (int i = 0; i < 10; i++) {
  //   UnloadTexture(gameState.earth->tex[i]);
  // }
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

  // pan region
  // Rectangle source;
  // source.x = gameState.source.x;
  // source.y = gameState.source.y;
  // source.width = gameState.dest.width;
  // source.height = gameState.dest.height;

  Shape *shape = gameState.shapes[gameState.currentShape];
  Vector3 pos = shape->Position(shape);
  float cameraPos[3] = {pos.x, pos.y, pos.z};
  SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos,
                 SHADER_UNIFORM_VEC3);

  BeginDrawing();

  ClearBackground(BLACK);
  // Earth *earth = gameState.earth;
  // if (gameState.now > earth->rate) {
  //   earth->rate = gameState.now + 1.0f;
  //   earth->current++;
  //   earth->current = CLAMPNUM(earth->current, 0, 9);
  // }

  // #ifndef PLATFORM_WEB
  //   SetTextureWrap(gameState.background, TEXTURE_WRAP_MIRROR_REPEAT);
  // #endif // PLATFORM_WEB
  //   DrawTexturePro(gameState.background, source, gameState.dest,
  //   gameState.origin,
  //                  gameState.rotation, WHITE);
  //   // DrawTexture(gameState.background, 0, 0, WHITE);
  //   DrawTextureEx(earth->tex[earth->current],
  //                 (Vector2){.x = gameState.dest.width * .6f,
  //                           .y = gameState.dest.height * .1f},
  //                 0.0f, 0.12, WHITE);

  BeginMode3D(gameState.camera);
  BeginShaderMode(shader);

  // DrawCube(Vector3Zero(), 2.0, 4.0, 2.0, WHITE);
  shape->Draw(shape);

  DrawPlane(Vector3Zero(), (Vector2){4.0, 4.0}, WHITE);
  // DrawCube(Vector3Zero(), 2.0, 4.0, 2.0, WHITE);

  EndShaderMode();

  EndMode3D();

  DrawFPS(10, 10);
  if (MENU_MODE == gameState.inputMode) {
    DrawMenu(gameState.menu, (Position){.x = 2, .y = 1});
  }
  EndDrawing();
}
