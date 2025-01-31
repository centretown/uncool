#include "davlib.h"

Shape *gameModels[] = {
    &(Shape){.typeID = MESH_POLY,
             .rate = 1.0f,
             .shapePtr =
                 &(ModelShape){
                     .model = {0},
                     .position = {1.0f, 1.0f, 1.0f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {0.2f, 0.2f, 0.2f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshPoly){
                             .sides = 12,
                             .radius = .4,
                         },
                 }},
    &(Shape){.typeID = MESH_PLANE,
             .rate = 1.0f,
             .shapePtr =
                 &(ModelShape){
                     .model = {0},
                     .position = {1.0f, 1.0f, 1.0f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {0.2f, 0.2f, 0.2f},
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
             .rate = 1.0f,
             .shapePtr =
                 &(ModelShape){
                     .model = {0},
                     .position = {1.0f, 1.0f, 1.0f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {0.2f, 0.2f, 0.2f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshCube){
                             .width = .5f,
                             .height = .5f,
                             .length = 1.0f,
                         },
                 }},
    &(Shape){.typeID = MESH_SPHERE,
             .rate = 1.0f,
             .shapePtr =
                 &(ModelShape){
                     .model = {0},
                     .position = {1.0f, 1.0f, 1.0f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {0.2f, 0.2f, 0.2f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshSphere){
                             .radius = .7f,
                             .rings = 20,
                             .slices = 20,
                         },
                 }},
    &(Shape){.typeID = MESH_HEMISPHERE,
             .rate = 1.0f,
             .shapePtr =
                 &(ModelShape){
                     .model = {0},
                     .position = {1.0f, 1.0f, 1.0f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {0.2f, 0.2f, 0.2f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshHemisphere){
                             .radius = .7f,
                             .rings = 20,
                             .slices = 20,
                         },
                 }},
    &(Shape){.typeID = MESH_CYLINDER,
             .rate = 1.0f,
             .shapePtr =
                 &(ModelShape){
                     .model = {0},
                     .position = {1.0f, 1.0f, 1.0f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {0.2f, 0.2f, 0.2f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshCylinder){
                             .radius = .7f,
                             .height = .2f,
                             .slices = 20,
                         },
                 }},
    &(Shape){.typeID = MESH_CONE,
             .rate = 1.0f,
             .shapePtr =
                 &(ModelShape){
                     .model = {0},
                     .position = {1.0f, 1.0f, 1.0f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {0.2f, 0.2f, 0.2f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshCone){
                             .radius = .7f,
                             .height = .2f,
                             .slices = 20,
                         },
                 }},
    &(Shape){.typeID = MESH_TORUS,
             .rate = 1.0f,
             .shapePtr =
                 &(ModelShape){
                     .model = {0},
                     .position = {1.0f, 1.0f, 1.0f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {0.2f, 0.2f, 0.2f},
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
             .rate = 1.0f,
             .shapePtr =
                 &(ModelShape){
                     .model = {0},
                     .position = {1.0f, 1.0f, 1.0f},
                     .rotationAxis = {0.0f, 0.0f, 0.0f},
                     .rotationAngle = 0.0f,
                     .scale = {0.2f, 0.2f, 0.2f},
                     .tint = WHITE,
                     .genPtr =
                         &(MeshKnot){
                             .radius = .7f,
                             .size = .5f,
                             .radSeg = 20,
                             .sides = 20,
                         },
                 }},
};
