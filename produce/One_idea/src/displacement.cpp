#include "displacement.h"
#include <iostream>

/*

Image GenerateDisplacementMap(Image image, int newWidth, int newHeight) {
    Image displacement = GenImageColor(newWidth, newHeight, BLACK);

    float scaleX = (float)newWidth / image.width;
    float scaleY = (float)newHeight / image.height;

    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            int originalX = (int)(x / scaleX);
            int originalY = (int)(y / scaleY);

            Color pixel = GetImageColor(image, originalX, originalY);
            unsigned char brightness = (pixel.r + pixel.g + pixel.b) / 2;

            unsigned char brightnessRight = (originalX < image.width - 1) ?
                (GetImageColor(image, originalX + 1, originalY).r + GetImageColor(image, originalX + 1, originalY).g + GetImageColor(image, originalX + 1, originalY).b) / 3 : brightness;
            unsigned char brightnessDown = (originalY < image.height - 1) ?
                (GetImageColor(image, originalX, originalY + 1).r + GetImageColor(image, originalX, originalY + 1).g + GetImageColor(image, originalX, originalY + 1).b) / 3 : brightness;

            int gradientX = brightnessRight - brightness;
            int gradientY = brightnessDown - brightness;

            unsigned char displacementX = (unsigned char)(gradientX + 128);
            unsigned char displacementY = (unsigned char)(gradientY + 128);

            ImageDrawPixel(&displacement, x, y, (Color){ displacementX, displacementY, 128, 255 });
        }
    }
    return displacement;
}

*/


Image GenerateDisplacementMap(Image image, int newWidth, int newHeight) {
    // Copier l'image pour la redimensionner
    Image resizedImage = ImageCopy(image);
    ImageResize(&resizedImage, newWidth, newHeight);

    // Obtenir les dimensions de l'image redimensionnée
    int width = resizedImage.width;
    int height = resizedImage.height;

    // Créer une nouvelle image pour la carte de déplacement
    Image displacementImage = GenImageColor(width, height, BLACK);

    // Accéder aux données des pixels de l'image d'entrée
    Color* inputPixels = LoadImageColors(resizedImage);
    if (!inputPixels) {
        std::cerr << "Erreur : Impossible de charger les couleurs de l'image." << std::endl;
        UnloadImage(resizedImage);
        return displacementImage; // Retourne l'image vide de déplacement
    }

    // Accéder aux données des pixels de l'image de déplacement
    Color* displacementPixels = (Color *)displacementImage.data;

    // Convertir l'image en niveaux de gris
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Color inputColor = inputPixels[y * width + x];
            // Calculer la valeur en niveaux de gris en utilisant les coefficients de luminosité
            unsigned char gray = (unsigned char)(inputColor.r * 0.3f + inputColor.g * 0.59f + inputColor.b * 0.11f);
            displacementPixels[y * width + x] = { gray, gray, gray, 255 };
        }
    }

    // Libérer les ressources
    UnloadImageColors(inputPixels);
    UnloadImage(resizedImage);  // Libérer l'image redimensionnée

    return displacementImage;
}

