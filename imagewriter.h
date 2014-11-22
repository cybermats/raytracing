#pragma once

#include <string>
#include <memory>

class ImageBuffer;

class ImageWriter
{
public:
    ImageWriter(std::shared_ptr<ImageBuffer> buffer);

    void savePNG(const std::string& filename) const;

private:
    std::shared_ptr<ImageBuffer> _buffer;
};

