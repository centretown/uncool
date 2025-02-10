
#include "davlib.h"
#include "raylib.h"
#include "uncool.h"

static Theme theme = (Theme){
    .backgroundColor = BLACK,
    .titleColor = (Color){.r = 0x00, .g = 0xf0, .b = 0x30, .a = 0xcf},
    .labelColor = (Color){.r = 0x00, .g = 0x89, .b = 0x79, .a = 0xcf},
    .valueColor = (Color){.r = 0x7b, .g = 0x4f, .b = 0x13, .a = 0xcf},

    .titleHover = (Color){.r = 0x00, .g = 0xf0, .b = 0x30, .a = 0xef},
    .labelHover = (Color){.r = 0x89, .g = 0x89, .b = 0x79, .a = 0xef},
    .valueHover = (Color){.r = 0x7b, .g = 0x4f, .b = 0x13, .a = 0xef},

    .titleActive = (Color){.r = 0x00, .g = 0xf0, .b = 0x30, .a = 0xff},
    .labelActive = (Color){.r = 0x00, .g = 0x89, .b = 0x79, .a = 0xff},
    .valueActive = (Color){.r = 0xcb, .g = 0x7f, .b = 0x13, .a = 0xff},
    .colorDim = (Color){.a = 96, .r = 96, .g = 255, .b = 255},
    .colorHover = (Color){.a = 255, .r = 96, .g = 255, .b = 255},

    .fontSize = 24,
    .padding = 24,
    .valueColumn = 15.0f,
};

static MenuItem *colorItems[] = {
    &(MenuItem){
        .itemType = MENU_INT,
        .label = "Red",
        .ivalue = 0,
        .imin = 0,
        .imax = 256,
        .iinc = 4,
        .onChoose = OnSetColorRed,
    },
    &(MenuItem){
        .itemType = MENU_INT,
        .label = "Green",
        .ivalue = 0,
        .imin = 0,
        .imax = 256,
        .iinc = 4,
        .onChoose = OnSetColorGreen,
    },
    &(MenuItem){
        .itemType = MENU_INT,
        .label = "Blue",
        .ivalue = 0,
        .imin = 0,
        .imax = 256,
        .iinc = 4,
        .onChoose = OnSetColorBlue,
    },
    &(MenuItem){
        .itemType = MENU_INT,
        .label = "Alpha",
        .ivalue = 0,
        .imin = 0,
        .imax = 256,
        .iinc = 4,
        .onChoose = OnSetColorAlpha,
    },
};

Menu colorMenuTemplate = (Menu){
    .title = "Colors",
    .current = 0,
    .itemCount = sizeof(colorItems) / sizeof(colorItems[0]),
    .items = colorItems,
};

static MenuItem *themeItems[] = {&(MenuItem){
                                     .itemType = MENU_CHOICE,
                                     .label = "Font Size",
                                     .choices =
                                         (char *[]){
                                             "24",
                                             "32",
                                             "40",
                                             "48",
                                             "56",
                                             "20",
                                         },
                                     .choiceCount = 6,
                                     .onChoose = OnChooseFont,
                                 },
                                 &(MenuItem){
                                     .itemType = MENU_SUB,
                                     .label = "Title Color",
                                     .menu = &colorMenuTemplate,
                                     .onPush = OnPushTitleColor,
                                 },
                                 &(MenuItem){
                                     .itemType = MENU_SUB,
                                     .label = "Title Active",
                                     .menu = &colorMenuTemplate,
                                     .onPush = OnPushTitleActive,
                                 },
                                 &(MenuItem){
                                     .itemType = MENU_SUB,
                                     .label = "Title Hover",
                                     .menu = &colorMenuTemplate,
                                     .onPush = OnPushTitleHover,
                                 },
                                 &(MenuItem){
                                     .itemType = MENU_SUB,
                                     .label = "Label Color",
                                     .menu = &colorMenuTemplate,
                                     .onPush = OnPushLabelColor,
                                 },
                                 &(MenuItem){
                                     .itemType = MENU_SUB,
                                     .label = "Label Active",
                                     .menu = &colorMenuTemplate,
                                     .onPush = OnPushLabelActive,
                                 },
                                 &(MenuItem){
                                     .itemType = MENU_SUB,
                                     .label = "Label Hover",
                                     .menu = &colorMenuTemplate,
                                     .onPush = OnPushLabelHover,
                                 },
                                 &(MenuItem){
                                     .itemType = MENU_SUB,
                                     .label = "Value Color",
                                     .menu = &colorMenuTemplate,
                                     .onPush = OnPushValueColor,
                                 },
                                 &(MenuItem){
                                     .itemType = MENU_SUB,
                                     .label = "Value Active",
                                     .menu = &colorMenuTemplate,
                                     .onPush = OnPushValueActive,
                                 },
                                 &(MenuItem){
                                     .itemType = MENU_SUB,
                                     .label = "Value Hover",
                                     .menu = &colorMenuTemplate,
                                     .onPush = OnPushValueHover,
                                 },
                                 &(MenuItem){
                                     .itemType = MENU_SUB,
                                     .label = "Background Color",
                                     .menu = &colorMenuTemplate,
                                     .onPush = OnPushBackgroundColor,
                                 },
                                 &(MenuItem){
                                     .itemType = MENU_SUB,
                                     .label = "Color Dim",
                                     .menu = &colorMenuTemplate,
                                     .onPush = OnPushColorDim,
                                 },
                                 &(MenuItem){
                                     .itemType = MENU_SUB,
                                     .label = "Color Hover",
                                     .menu = &colorMenuTemplate,
                                     .onPush = OnPushColorHover,
                                 }};

Menu themeMenu = (Menu){
    .title = "Theme",
    .current = 0,
    .itemCount = sizeof(themeItems) / sizeof(themeItems[0]),
    .items = themeItems,
};

static MenuItem *menuItems[] = {
    &(MenuItem){
        .itemType = MENU_SUB,
        .label = "Theme",
        .menu = &themeMenu,
    },
    &(MenuItem){
        .itemType = MENU_CHOICE,
        .label = "Select Shape",
        .choices =
            (char *[]){
                "Mesh Poly",
                "Mesh Plane",
                "Mesh Cube",
                "Mesh Sphere",
                "Mesh Hemisphere",
                "Mesh Cylinder",
                "Mesh Cone",
                "Mesh Torus",
                "Mesh Knot",
                "Red Cube",
                "Blue Sphere",
                "Green Capsule",
                "Yellow Cylinder",
            },
        .choiceCount = 12,
        .onChoose = OnChooseShape,
    },
    &(MenuItem){
        .itemType = MENU_CHOICE,
        .label = "Current Mode",
        .choices =
            (char *[]){
                "Move Object",
                "Move Camera Position",
                "Move Camera Target",
                "Move Camera Up",
                "Change Fovy",
                "Move Background",
            },
        .choiceCount = 6,
        .onChoose = OnChooseMode,
    },
};

Menu menu = (Menu){
    .title = "Settings",
    .current = 0,
    .itemCount = sizeof(menuItems) / sizeof(menuItems[0]),
    .items = menuItems,
};

#include "shapes.c"

const Camera cameraOrigin = (Camera){
    .position = (Vector3){.x = 3.0f, .y = 3.0f, .z = 2.0f},
    .target = (Vector3){.x = 0.0f, .y = 0.0f, .z = 0.0f},
    .up = (Vector3){.x = 0.0f, .y = 1.0f, .z = 0.0f},
    .fovy = 60.0f,
    .projection = CAMERA_PERSPECTIVE,
};

GameState gameState = (GameState){
    .camera = cameraOrigin,
    .origin = cameraOrigin,
    .moveMode = MODE_MOVE_SHAPE,
    .inputMode = GAME_MODE,
    .labelColor = YELLOW,
    .valueColor = ORANGE,
    .theme = &theme,
    .menuPos = (Rectangle){.x = 5, .y = 2, .width = 16.0f, .height = 16.0f},
    .menu = &menu,
    .shapes = gameShapes,
    .currentShape = 0,
    .shapeCount = sizeof(gameShapes) / sizeof(gameShapes[0]),
};
