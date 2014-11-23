#include "imagereader.h"

#include "imagebuffer.h"
#include "lodepng.h"

#include "utils.h"

std::unique_ptr<ImageBuffer> ImageReader::readPNG(const std::string& filename)
{
    std::vector<unsigned char> buffer;
    unsigned int width, height;
    unsigned int error = lodepng::decode(buffer, width, height, filename);
    auto image = make_unique<ImageBuffer>(width, height);

    auto iit = buffer.cbegin();
    auto oit = image->begin();

    while(iit != buffer.cend())
    {
        double r = *(iit++) * 255;
        double g = *(iit++) * 255;
        double b = *(iit++) * 255;
        double a = *(iit++) * 255;
        *(oit++) = Color(r, g, b, a);
    }
    return image;
}
