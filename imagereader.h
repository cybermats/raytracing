#pragma once

#include <memory>
#include <string>

class ImageBuffer;

class ImageReader
{
public:
    static std::unique_ptr<ImageBuffer> readPNG(const std::string& filename);
};
