#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Pour la fonction usleep
#include <math.h>    // Pour la fonction sinf

// Fonction pour convertir une image en niveaux de gris
void ConvertImageToGrayLevels(Image image, const char* outputFilename) {
    int width = image.width;
    int height = image.height;
    Color* pixels = LoadImageColors(image);

    int byteWidth = (width + 1) / 2;  // 2 pixels par byte
    unsigned char* grayData = (unsigned char*)malloc(byteWidth * height);
    if (!grayData) {
        printf("Memory allocation failed!\n");
        return;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x += 2) {
            int index = y * byteWidth + x / 2;

            Color pixel1 = pixels[y * width + x];
            Color pixel2 = (x + 1 < width) ? pixels[y * width + (x + 1)] : (Color){ 0 };

            // Convertir en niveaux de gris
            unsigned char gray1 = (unsigned char)(0.299f * pixel1.r + 0.587f * pixel1.g + 0.114f * pixel1.b);
            unsigned char gray2 = (unsigned char)(0.299f * pixel2.r + 0.587f * pixel2.g + 0.114f * pixel2.b);

            // Définir les niveaux de gris en fonction de la luminance
            unsigned char grayLevel1 = gray1 / 16;
            unsigned char grayLevel2 = gray2 / 16;

            // Combinaison des niveaux de gris des deux pixels
            unsigned char combinedGray = (grayLevel1 << 4) | grayLevel2;

            grayData[index] = combinedGray;
        }
    }

    // Écriture du fichier binaire
    FILE* file = fopen(outputFilename, "wb");
    if (file) {
        fwrite(grayData, 1, byteWidth * height, file);
        fclose(file);
        printf("Binary file \"%s\" generated successfully.\n", outputFilename);
    } else {
        printf("Failed to open output file!\n");
    }

    // Nettoyage
    free(grayData);
    UnloadImageColors(pixels);
}

// Fonction pour générer une onde sonore simple (bip)
Wave GenerateSineWave(float frequency, float duration, int sampleRate) {
    int sampleCount = (int)(duration * sampleRate);
    Wave wave = { 0 };
    wave.frameCount = sampleCount;
    wave.sampleRate = sampleRate;
    wave.sampleSize = 16;  // 16-bit audio
    wave.channels = 1;  // Mono

    short *samples = (short *)malloc(sampleCount * sizeof(short));

    for (int i = 0; i < sampleCount; i++) {
        samples[i] = (short)(32760 * sinf(2.0f * PI * frequency * ((float)i / sampleRate)));
    }

    wave.data = samples;

    return wave;
}

// Fonction pour lire et jouer des sons basés sur le fichier binaire de niveaux de gris
void PlaySoundFromGrayBinaryFile(const char* filename, int width, int height) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    int byteWidth = (width + 1) / 2;
    long fileSize = byteWidth * height;

    unsigned char* buffer = (unsigned char*)malloc(fileSize);
    if (buffer) {
        fread(buffer, 1, fileSize, file);
        fclose(file);
        printf("Binary file \"%s\" loaded successfully.\n", filename);

        InitAudioDevice();

        // Initialiser Raylib pour l'affichage de l'image
        InitWindow(800, 600, "Image Reconstruction");
        SetTargetFPS(60);

        // Boucle pour jouer les sons et afficher l'image en niveaux de gris en temps réel
        RenderTexture2D target = LoadRenderTexture(width, height);
        BeginTextureMode(target);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x += 2) {
                int index = y * byteWidth + x / 2;

                unsigned char grayLevel = buffer[index];

                // Dessiner les deux pixels correspondants sur la RenderTexture
                Color pixelColor1, pixelColor2;
                int grayIndex1 = (grayLevel >> 4) & 0x0F;
                int grayIndex2 = grayLevel & 0x0F;

                float grayValue1 = (float)grayIndex1 / 15.0f;
                float grayValue2 = (float)grayIndex2 / 15.0f;

                pixelColor1 = pixelColor2 = (Color){ (unsigned char)(255 * grayValue1), (unsigned char)(255 * grayValue1), (unsigned char)(255 * grayValue1), 255 };

                DrawPixel(x, y, pixelColor1);
                if (x + 1 < width) DrawPixel(x + 1, y, pixelColor2);

                // Mettre à jour l'affichage de l'image
                EndTextureMode();
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);
                EndDrawing();
                BeginTextureMode(target);

                // Générer un son correspondant au niveau de gris
                float frequency = 220.0f + 220.0f * ((float)grayIndex1 / 15.0f);
                Wave wave = GenerateSineWave(frequency, 0.1f, 44100);  // Générer un bip de 0.1 seconde
                Sound beep = LoadSoundFromWave(wave);
                PlaySound(beep);
                printf("Playing sound for pixel (%d, %d): frequency=%.2f Hz\n", x, y, frequency);

                // Ajouter un court délai pour séparer les sons
                usleep(100000);  // 100 millisecondes entre les bips
                UnloadSound(beep);
                UnloadWave(wave);
            }
        }

        // Libérer la mémoire utilisée par la RenderTexture
        EndTextureMode();
        UnloadRenderTexture(target);

        CloseAudioDevice();

        free(buffer);
    } else {
        printf("Memory allocation failed!\n");
        fclose(file);
    }
}

int main(void) {
    // Charger l'image
    const char* inputImagePath = "./ressources/displacement/a.png";  // Remplacer par le chemin de votre image
    const char* outputGrayBinaryPath = "output_gray.bin";  // Chemin de sortie pour le fichier binaire niveaux de gris
    Image image = LoadImage(inputImagePath);
    if (image.data == NULL) {
        printf("Failed to load image!\n");
        return 1;
    }

    // Convertir l'image en niveaux de gris
    ConvertImageToGrayLevels(image, outputGrayBinaryPath);

    // Jouer les sons basés sur le fichier binaire de niveaux de gris
    PlaySoundFromGrayBinaryFile(outputGrayBinaryPath, image.width, image.height);

    // Libérer l'image
    UnloadImage(image);

    // Fermer la fenêtre Raylib
    CloseWindow();

    printf("Conversion and sound playback completed.\n");

    return 0;
}
