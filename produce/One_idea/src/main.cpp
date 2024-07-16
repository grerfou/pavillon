#include "raylib.h"
#include "displacement.h"
#include "binary_conversion.h"
#include "scene.h"

Scene3D scene;

float scaleFactor = 0.019f;
float displacementScale = -0.3f; //0.2
int step = 3;

float totalRotation = 10.0f;
float rotationSpeed = 0.005f;

int ImageWidth = 1024;
int ImageHeight= 1024;

int main() 
{
    InitWindow(1750, 1050, "Displacement Map Generation");

    Image image = LoadImage("ressources/images/b.png");
    Image displacement = GenerateDisplacementMap(image, ImageWidth, ImageHeight);

    ExportImage(displacement, "ressources/displacement/displacement.png");
    ConvertImageToBinary("ressources/displacement/displacement.png", "ressources/bin/displacement.bin");

    UnloadImage(image);
    UnloadImage(displacement);

    InitScene3D(&scene);

    while (!WindowShouldClose())
    {
        totalRotation += rotationSpeed;
        DrawScene3D(&scene, scaleFactor, displacementScale, totalRotation, step);
    }

    UnloadScene3D(&scene);
    CloseWindow();

    return 0;
}

