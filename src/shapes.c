#include "davlib.h"

static const Vector3 position = {1.0f, 1.0f, 1.0f};
static const Vector3 rate = {0.05f, 1.0f, 0.05f};

Shape *gameShapes[] = {
    &(Shape){.typeID = MESH_POLY,
             .rate = rate,
             .shapePtr =
                 &(MeshShape){
                     // .model = {0},
                     .position = {0.5f, 0.5f, 0.5f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {2.0f, 4.0f, 2.0f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshPoly){
                             .sides = 12,
                             .radius = .4,
                         },
                 }},
    &(Shape){.typeID = MESH_PLANE,
             .rate = rate,
             .shapePtr =
                 &(MeshShape){
                     // .model = {0},
                     .position = {0.5f, 0.5f, 0.5f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {2.0f, 4.0f, 2.0f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshPlane){
                             .width = .5,
                             .length = .5,
                             .resX = 16,
                             .resZ = 8,
                         },
                 }},
    &(Shape){.typeID = MESH_CUBE,
             .rate = rate,
             .shapePtr =
                 &(MeshShape){
                     // .model = {0},
                     .position = {0.5f, 0.5f, 0.5f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {2.0f, 4.0f, 2.0f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshCube){
                             .width = .5f,
                             .height = .5f,
                             .length = 1.0f,
                         },
                 }},
    &(Shape){.typeID = MESH_SPHERE,
             .rate = rate,
             .shapePtr =
                 &(MeshShape){
                     // .model = {0},
                     .position = {0.5f, 0.5f, 0.5f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {2.0f, 4.0f, 2.0f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshSphere){
                             .radius = .7f,
                             .rings = 20,
                             .slices = 20,
                         },
                 }},
    &(Shape){.typeID = MESH_HEMISPHERE,
             .rate = rate,
             .shapePtr =
                 &(MeshShape){
                     // .model = {0},
                     .position = {0.5f, 0.5f, 0.5f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {2.0f, 4.0f, 2.0f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshHemisphere){
                             .radius = .7f,
                             .rings = 20,
                             .slices = 20,
                         },
                 }},
    &(Shape){.typeID = MESH_CYLINDER,
             .rate = rate,
             .shapePtr =
                 &(MeshShape){
                     // .model = {0},
                     .position = {0.5f, 0.5f, 0.5f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {2.0f, 2.0f, 2.0f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshCylinder){
                             .radius = .2f,
                             .height = .2f,
                             .slices = 20,
                         },
                 }},
    &(Shape){.typeID = MESH_CONE,
             .rate = rate,
             .shapePtr =
                 &(MeshShape){
                     // .model = {0},
                     .position = {0.5f, 0.5f, 0.5f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {2.0f, 4.0f, 2.0f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshCone){
                             .radius = .7f,
                             .height = .2f,
                             .slices = 20,
                         },
                 }},
    &(Shape){.typeID = MESH_TORUS,
             .rate = rate,
             .shapePtr =
                 &(MeshShape){
                     // .model = {0},
                     .position = {0.5f, 0.5f, 0.5f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {2.0f, 4.0f, 2.0f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshTorus){
                             .radius = .7f,
                             .size = .5f,
                             .radSeg = 20,
                             .sides = 20,
                         },
                 }},
    &(Shape){.typeID = MESH_KNOT,
             .rate = rate,
             .shapePtr =
                 &(MeshShape){
                     // .model = {0},
                     .position = {0.5f, 0.5f, 0.5f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {2.0f, 4.0f, 2.0f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshKnot){
                             .radius = .7f,
                             .size = .5f,
                             .radSeg = 20,
                             .sides = 20,
                         },
                 }},
    &(Shape){.typeID = CUBE,
             .rate = rate,
             .shapePtr =
                 &(CubeShape){
                     .position = position,
                     .size = (Vector3){0.4f, 0.4f, 0.4f},
                     .color = RED,
                 }},
    &(Shape){.typeID = SPHERE,
             .rate = rate,
             .shapePtr =
                 &(SphereShape){
                     .position = position,
                     .radius = 0.2f,
                     .color = BLUE,
                 }},
    &(Shape){.typeID = CAPSULE,
             .rate = rate,
             .shapePtr =
                 &(CapsuleShape){
                     .startPos = position,
                     .endPos = (Vector3){.x = position.x + .4,
                                         .y = position.y + .4,
                                         .z = position.z + .4},
                     .radius = 0.1f,
                     .slices = 40,
                     .rings = 10,
                     .color = GREEN,
                 }},
    &(Shape){.typeID = CYLINDER,
             .rate = rate,
             .shapePtr =
                 &(CylinderShape){
                     .position = position,
                     .radiusTop = .1f,
                     .radiusBottom = .2f,
                     .height = .2,
                     .slices = 40,
                     .color = YELLOW,
                 }},
};
