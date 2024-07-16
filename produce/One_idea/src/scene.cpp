#include "scene.h"
#include "raylib.h"
#include <math.h>


void InitScene3D(Scene3D *scene) 
{
    // Load Displacement Image 
    Image displacementImage = LoadImage("ressources/displacement/displacement.png");
    if (displacementImage.data == NULL) 
    {
        TraceLog(LOG_ERROR, "Failed to load Image Color");
        return;
    }

    scene->width = displacementImage.width;
    scene->height = displacementImage.height;

    // Create point Cloud 
    scene->pixels = LoadImageColors(displacementImage);
    if (scene->pixels == NULL) 
    {
        TraceLog(LOG_ERROR, "Failed to load image color");
        UnloadImage(displacementImage);
        return;
    }
    UnloadImage(displacementImage);

    // Initialize camera
    scene->camera.position = (Vector3){ 30.0f, 5.0f, 25.0f };
    scene->camera.target = (Vector3){ 0.0f, 0.5f, 0.0f };
    scene->camera.up = (Vector3){ 5.0f, 10.0f, 5.0f };  // corrected to 1.0f to be a valid up vector
    scene->camera.fovy = 45.0f;
    scene->camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);
}

void DrawScene3D(Scene3D *scene, float scaleFactor, float displacementScale, float totalRotation, int step) 
{
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(scene->camera);

    Vector3 rotationCenter = { scene->width * scaleFactor / 2.0f, 0.0f, scene->height * scaleFactor / 2.0f };

    // Draw Point cloud and rotation  
    for (int z = 0; z < scene->height; z += step) 
    {
        for (int x = 0; x < scene->width; x += step) 
        {
            int index = z * scene->width + x;

            // height of pixels and scale 
            float y = (float)scene->pixels[index].r * displacementScale;  // Assuming red channel holds height data
            float rotatedX = (float)x * scaleFactor - rotationCenter.x;
            float rotatedZ = (float)z * scaleFactor - rotationCenter.z;
            float newX = rotatedX * cosf(totalRotation) - rotatedZ * sinf(totalRotation);
            float newZ = rotatedX * sinf(totalRotation) + rotatedZ * cosf(totalRotation);
            DrawPoint3D((Vector3){newX + rotationCenter.x, y * scaleFactor, newZ + rotationCenter.z}, RED);
        }
    }

    EndMode3D();
    EndDrawing();
}

void UnloadScene3D(Scene3D *scene)
{
    if (scene->pixels != NULL) 
    {
        UnloadImageColors(scene->pixels);
    }
}

