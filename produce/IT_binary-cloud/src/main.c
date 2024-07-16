#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>    

#define MAX_POINTS 32768

typedef struct {
    Vector3 position;
    Color color;
} Point3D;

// Fonction pour générer une onde sonore simple (bip)
Wave GenerateSineWave(float frequency, float duration, int sampleRate) {
    int sampleCount = (int)(duration * sampleRate);
    Wave wave = { 0 };
    wave.frameCount = sampleCount;
    wave.sampleRate = sampleRate;
    wave.sampleSize = 16;             // 16-bit audio
    wave.channels = 1;                // Mono  

    short *samples = (short *)malloc(sampleCount * sizeof(short));

    for (int i = 0; i < sampleCount; i++) {
        samples[i] = (short)(32760 * sinf(2.0f * PI * frequency * ((float)i / sampleRate)));
    }

    wave.data = samples;
    return wave;
}

void PlaySoundAndDrawPointCloudFromBinaryFile(const char* filename, int width, int height) {
    InitAudioDevice();

    Camera camera = { 0 };
    camera.position = (Vector3){ -113.66f, 142.12f, -296.15f };
    camera.target = (Vector3){ 200.33f, 50.92f, 314.54f };
    camera.up = (Vector3){ 2.0f, 2.0f, 2.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    int screenWidth = 1920; 
    int screenHeight = 1170; 
    InitWindow(screenWidth, screenHeight, "Nuage de points 3D et Son en temps réel");
    SetTargetFPS(60);

    Color backgroundColor = { 63, 83, 215, 255 };

    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Échec de l'ouverture du fichier : %s\n", filename);
        CloseAudioDevice();
        CloseWindow();
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(fileSize);
    if (!buffer) {
        printf("Échec d'allocation mémoire!\n");
        fclose(file);
        CloseAudioDevice();
        CloseWindow();
        return;
    }

    fread(buffer, 1, fileSize, file);
    Sound beep = { 0 };
    Wave wave = { 0 };

    Point3D points[MAX_POINTS] = { 0 };
    int pointCount = 0;
    bool shouldRestart = false;

    while (!WindowShouldClose()) {
        if (shouldRestart || pointCount >= MAX_POINTS) {
            pointCount = 0;
            shouldRestart = false;
            // Pour recommencer à lire depuis le début du fichier
            fseek(file, 0, SEEK_SET);
        }

        if (pointCount < fileSize) {
            BeginDrawing();
            ClearBackground(backgroundColor);

            BeginMode3D(camera);

            Vector3 rotationCenter = { (float)width / 2.0f, 0.0f, (float)height / 2.0f };

            int value = buffer[pointCount];

            float x = (float)(pointCount % width) - rotationCenter.x;
            float y = (float)value / 25.5f;
            float z = (float)(pointCount / width) - rotationCenter.z;

            if (pointCount > 0) {
                // Dessiner tous les points générés jusqu'à présent
                for (int i = 0; i < pointCount; ++i) {
                    DrawCubeV(points[i].position, (Vector3){ 0.5f, 0.5f, 0.5f }, points[i].color);
                }
            }

            points[pointCount].position = (Vector3){ x + rotationCenter.x, y, z + rotationCenter.z };
            points[pointCount].color = (Color){ value, value, value, 255 };

            // Générer et jouer l'onde sonore
            float frequency = 220.0f + (value / 255.0f) * 220.0f; // Fréquence varie entre 220 Hz et 440 Hz
            wave = GenerateSineWave(frequency, 0.1f, 44100);

            if (!IsSoundPlaying(beep)) {
                beep = LoadSoundFromWave(wave);
                PlaySound(beep);
            }

            UnloadWave(wave); // Décharger immédiatement pour éviter les fuites de mémoire
            EndMode3D();
            EndDrawing();
            pointCount++;
        } else {
            shouldRestart = true;
        }
    }

    UnloadSound(beep);
    fclose(file);
    free(buffer);
    CloseAudioDevice();
    CloseWindow();
}

int main(void) {
    const char* filename = "output_grayscale.bin";
    int width = 256;
    int height = 256;

    PlaySoundAndDrawPointCloudFromBinaryFile(filename, width, height);
    return 0;
}
