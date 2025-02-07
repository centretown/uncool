// uncool
#define DAVLIB_IMPLEMENTATION
#include "uncool.h"
#include "davlib.h"

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

// in gamestate.c
extern GameState gameState, initialState;

static Shader shader = {0};
static int ambientLoc = 0;
static Light lights[MAX_LIGHTS] = {0};

// Create lights
void CreateLights(Shader shader) {
  lights[0] = CreateLight(LIGHT_POINT, (Vector3){-2, 1, -2}, Vector3Zero(),
                          YELLOW, shader);
  lights[1] =
      CreateLight(LIGHT_POINT, (Vector3){2, 1, 2}, Vector3Zero(), RED, shader);
  lights[2] = CreateLight(LIGHT_POINT, (Vector3){-2, 1, 2}, Vector3Zero(),
                          GREEN, shader);
  lights[3] = CreateLight(LIGHT_POINT, (Vector3){2, 1, -2}, Vector3Zero(), BLUE,
                          shader);
}

void LoadTextures() {
  // load resources
  gameState.menuInactivePic = LoadTexture("resources/menu-20.png");
  gameState.menuActivePic = LoadTexture("resources/menu_open-20.png");
  gameState.menu->leftArrow = LoadTexture("resources/left-20.png");
  gameState.menu->rightArrow = LoadTexture("resources/right-20.png");

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

  gameState.projection = LoadTexture("wood.jpg");
  gameState.material = LoadMaterialDefault();
  gameState.material.shader = shader; // Set shader effect to 3d model
  // texture gets bound to models
  gameState.material.maps[MATERIAL_MAP_ROUGHNESS].texture =
      gameState.projection;
  gameState.material.maps[MATERIAL_MAP_DIFFUSE].color =
      (Color){.r = 0, .g = 255, .b = 0, .a = 255};

  if (!IsMaterialValid(gameState.material)) {
    printf("MATERIAL INVALID\n");
  }
}

static Color colorDim = (Color){.a = 63, .r = 96, .g = 255, .b = 255};
static Color colorHover = (Color){.a = 255, .r = 96, .g = 255, .b = 255};

void Load() {
  gameState.menu->custom = &gameState;
  initialState = gameState;

  // Set MSAA 4X hint before windows creation
  SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT |
                 FLAG_WINDOW_MAXIMIZED);
  SetTraceLogLevel(LOG_NONE);

  InitWindow(1260, 720, "Centretown - UNCOOL");
  int monitor = GetCurrentMonitor();
  SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
  SetWindowPosition(0, 0);

  LoadTextures();
  CreateLights(shader);

  InitShapes(gameState.shapeCount, gameState.shapes, gameState.material);
}

void Unload() {
  for (int i = 0; i < gameState.shapeCount; i++) {
    gameState.shapes[i]->Unload(gameState.shapes[i]);
  }
  UnloadShader(shader); // Unload shader
  // UnloadTexture(gameState.background);
  UnloadTexture(gameState.projection);
  UnloadTexture(gameState.menuInactivePic);
  UnloadTexture(gameState.menuActivePic);
  UnloadTexture(gameState.menu->leftArrow);
  UnloadTexture(gameState.menu->rightArrow);
}

// Update and draw game frame
void Loop(void) {
  gameState.now = GetTime();
  gameState.menu->mousePos = GetMousePosition();

  Shape *shape = gameState.shapes[gameState.currentShape];
  Vector3 pos = shape->Position(shape);
  float cameraPos[3] = {pos.x, pos.y, pos.z};
  SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos,
                 SHADER_UNIFORM_VEC3);

  BeginDrawing();
  ClearBackground(gameState.backgroundColor);
  BeginMode3D(gameState.camera);
  BeginShaderMode(shader);
  shape->Draw(shape);
  DrawPlane(Vector3Zero(), (Vector2){4.0, 4.0}, WHITE);
  EndShaderMode();
  EndMode3D();
  // DrawFPS(10, 10);
  Rectangle menuPos = (Rectangle){.x = 5,
                                  .y = 2,
                                  .width = gameState.menuActivePic.width,
                                  .height = gameState.menuActivePic.height};
  int cmd = InputMouse(1, &menuPos, gameState.now, gameState.menu->mousePos);
  if (CMD_NONE != cmd) {
    if (gameState.inputMode == GAME_MODE) {
      gameState.inputMode = MENU_MODE;
    } else {
      gameState.inputMode = GAME_MODE;
    }
  }

  if (gameState.inputMode == GAME_MODE) {
    DrawTexture(gameState.menuInactivePic, 2, 2, colorDim);
  } else {
    DrawTexture(gameState.menuActivePic, 2, 2, colorHover);
    InputMouseMenu(gameState.menu, gameState.now);
    DrawMenu(gameState.menu,
             (Position){.x = menuPos.x, .y = menuPos.y + menuPos.height});
  }

  if (IsWindowFocused()) {
    gameState.inputMode = UpdateMode(gameState.inputMode, gameState.now);
    if (gameState.inputMode == MENU_MODE) {
      int cmd = InputNav(gameState.now);
      NavigateMenu(cmd, gameState.menu, gameState.now);
    } else { // GAME_MODE
      UpdateState(&gameState, &initialState);
    }
  }
  EndDrawing();
}

int main() {
  Load();

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(Loop, 60, 1);
#else
  SetTargetFPS(60);            // Set our game to run at 60 frames-per-second
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    Loop();
  }
#endif

  Unload();
  return 0;
}
