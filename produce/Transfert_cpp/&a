#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h> // For usleep

#define MAX_POINTS 16384

Camera3D camera;

typedef struct {
    Vector3 position;
    Color color;
} Point3D;

typedef struct Wave {
    unsigned int sampleRate;
    unsigned int sampleSize;
    unsigned int channels;
    unsigned int frameCount;
    short *data; // Pointeur vers les données audio
} Wave;

// Function prototypes
void PlaySoundAndDrawPointCloud(const unsigned char* buffer, int fileSize, int width, int height);
void UpdatePointCloud(Point3D* points, const unsigned char* buffer, int pointCount);
void DrawPointCloud(Point3D* points, int pointCount);
void DrawReconstructedImage(Texture2D reconstructedTexture, Image image, int screenWidth, int screenHeight);
void DrawCameraPosition(Camera camera);

int main(void) {
    const char* filename = "output.bin";
    int width = 256;
    int height = 256;

    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(fileSize);
    if (!buffer) {
        printf("Memory allocation failed!\n");
        fclose(file);
        return 1;
    }

    fread(buffer, 1, fileSize, file);
    fclose(file);
    printf("Binary file \"%s\" loaded successfully.\n", filename);

    PlaySoundAndDrawPointCloud(buffer, fileSize, width, height);

    free(buffer);

    return 0;
}

// Play sound and draw point cloud
void PlaySoundAndDrawPointCloud(const unsigned char* buffer, int fileSize, int width, int height) {
    InitAudioDevice();

    Camera camera = { 0 };
    camera.position = (Vector3){ -30.76f, 400.92f, -5.51f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    int screenWidth = 1920;
    int screenHeight = 1170;
    InitWindow(screenWidth, screenHeight, "Binary Point Cloud and Image Reconstruction");
    SetTargetFPS(60);

    // Create a blank image to draw reconstructed pixels
    Image image = GenImageColor(width, height, BLACK);
    Texture2D reconstructedTexture = LoadTextureFromImage(image);
    UnloadImage(image);

    Point3D points[MAX_POINTS] = { 0 };
    int pointCount = 0;

    while (!WindowShouldClose() && pointCount < fileSize) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        UpdatePointCloud(points, buffer, pointCount);
        DrawPointCloud(points, pointCount);
        DrawReconstructedImage(reconstructedTexture, image, screenWidth, screenHeight);
        DrawCameraPosition(camera);

        EndDrawing();

        // Play sound for the current point
        int value = buffer[pointCount];
        float frequency = 220.0f + (value / 255.0f) * 220.0f;

        Wave wave = { 0 };
        wave.sampleRate = 44100;
        wave.sampleSize = 16;
        wave.channels = 1;
        wave.frameCount = (int)(0.1f * wave.sampleRate);

        // Cast explicite pour indiquer le type
        wave.data = (short *)malloc(wave.frameCount * sizeof(short));
        if (wave.data) {
            for (int i = 0; i < wave.frameCount; i++) {
                wave.data[i] = (short)(32760 * sinf(2.0f * PI * frequency * ((float)i / wave.sampleRate)));
            }

            // Load sound from wave data
            Sound beep = LoadSoundFromWave(wave);
            PlaySound(beep);
            UnloadSound(beep);
            free(wave.data);
        }

        // Update reconstructed image in the buffer
        Color pixelColor = (Color){ (unsigned char)value, (unsigned char)value, (unsigned char)value, 255 };
        ImageDrawPixel(&image, pointCount % width, pointCount / width, pixelColor);

        // Update texture with image data
        UpdateTexture(reconstructedTexture.texture, image.data);

        // Increment point count
        pointCount++;

        // Delay between points
        usleep(10000);
    }

    UnloadTexture(reconstructedTexture);
    CloseAudioDevice();
    CloseWindow();
}

// Update point cloud
void UpdatePointCloud(Point3D* points, const unsigned char* buffer, int pointCount) {
    for (int i = 0; i < pointCount; i++) {
        points[i].position = (Vector3){ (float)(i % 256), (float)(buffer[i] / 10.0f), (float)(i / 256) };
        points[i].color = (Color){ (unsigned char)buffer[i], (unsigned char)buffer[i], (unsigned char)buffer[i], 255 };
    }
}

// Draw point cloud
void DrawPointCloud(Point3D* points, int pointCount) {
    BeginMode3D(camera);
    for (int i = 0; i < pointCount; i++) {
        DrawCubeV(points[i].position, (Vector3){ 0.5f, 0.5f, 0.5f }, points[i].color);
    }
    EndMode3D();
}

// Draw reconstructed image
void DrawReconstructedImage(Texture2D reconstructedTexture, Image image, int screenWidth, int screenHeight) {
    DrawTexturePro(reconstructedTexture, (Rectangle){ 0, 0, (float)reconstructedTexture.width, (float)-reconstructedTexture.height },
                   (Rectangle){ (float)screenWidth / 2.0f, 0, (float)screenWidth / 2.0f, (float)screenHeight },
                   (Vector2){ 0, 0 }, 0.0f, WHITE);
}

// Draw camera position
void DrawCameraPosition(Camera camera) {
    DrawText(TextFormat("Camera Position: (%.2f, %.2f, %.2f)", camera.position.x, camera.position.y, camera.position.z),
             10, 10, 20, RED);
}

