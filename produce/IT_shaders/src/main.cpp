#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <cassert>
#include <memory>

// Undefine the PI macro defined in raylib.h
#ifdef PI
    #undef PI
#endif

#include "raylib.h"

const float PI = 3.14159265359f;

std::vector<int> LoadPixelData(const char* filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier binaire pour lecture." << std::endl;
        return {};
    }

    std::vector<int> luminosities;
    int luminosity;
    while (inFile.read(reinterpret_cast<char*>(&luminosity), sizeof(int))) {
        luminosities.push_back(luminosity);
    }

    inFile.close();
    return luminosities;
}

std::unique_ptr<short[]> GenerateWaveData(float frequency, unsigned int sampleRate, unsigned int sampleCount) {
    auto waveData = std::make_unique<short[]>(sampleCount);
    for (unsigned int i = 0; i < sampleCount; ++i) {
        waveData[i] = static_cast<short>(std::sin(2.0f * PI * frequency * (static_cast<float>(i) / sampleRate)) * SHRT_MAX);
    }
    return waveData;
}

int main() {
    const char* binaryFile = "./displacement_map.bin";

    std::vector<int> luminosities = LoadPixelData(binaryFile);
    if (luminosities.empty()) {
        return 1;
    }

    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Génération de son depuis une image en niveaux de gris");

    InitAudioDevice();

    unsigned int sampleRate = 44100;
    float duration = 0.1f;
    float freqLow = 440.0f;
    float freqHigh = 880.0f;

    for (size_t index = 0; index < luminosities.size(); ++index) {
        int value = luminosities[index];
        unsigned int sampleCount = static_cast<unsigned int>(duration * sampleRate);

        assert(sampleCount > 0);
        assert(sampleRate > 0);

        float frequency = (value <= 127) ? freqLow : freqHigh;
        auto waveData = GenerateWaveData(frequency, sampleRate, sampleCount);

        assert(waveData != nullptr);

        Wave wave = {
            .frameCount = sampleCount,
            .sampleRate = sampleRate,
            .sampleSize = 16,
            .channels = 1,
            .data = waveData.get()
        };

        Sound sound = LoadSoundFromWave(wave);
        assert(sound.stream.buffer != nullptr);

        PlaySound(sound);
        while (IsSoundPlaying(sound)) {
        }

        UnloadSound(sound);
        std::cout << "Son à l'index " << index << " joué et déchargé avec succès." << std::endl;
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
