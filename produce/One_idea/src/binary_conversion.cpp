#include "binary_conversion.h"
#include <fstream>

void ConvertImageToBinary(const std::string& inputImagePath, const std::string& outputBinaryPath)
{
  Image image = LoadImage(inputImagePath.c_str());

  if (image.data != nullptr)
  {
    std::ofstream outFile(outputBinaryPath, std::ios::binary);

    for (int y = 0; y < image.height; y++)
    {
      for (int x = 0; x < image.width; x++)
      {
        Color pixel = GetImageColor(image, x, y);
        outFile.write(reinterpret_cast<char*>(&pixel), sizeof(Color));
      }
    }

    outFile.close();
    UnloadImage(image);
  } else 
  {
    TraceLog(LOG_ERROR, "Failed to load image: %s", inputImagePath.c_str());
  }
}
