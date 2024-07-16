#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"

// Définition complète de la structure Scene3D
typedef struct Scene3D {
    Camera camera;
    Color *pixels;
    int width;
    int height;
} Scene3D;

void InitScene3D(Scene3D *scene);
void DrawScene3D(Scene3D *scene, float scaleFactor, float displacementScale, float totalRotation, int step);
void UnloadScene3D(Scene3D *scene);

#endif // SCENE_H

