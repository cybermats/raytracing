#include "imagereader.h"

#include "imagebuffer.h"
#include "lodepng.h"

#include "utils.h"
#include <iostream>

std::unique_ptr<ImageBuffer> ImageReader::readPNG(const std::string& filename)
{
    std::vector<unsigned char> buffer;
    unsigned int width, height;
    unsigned int error = lodepng::decode(buffer, width, height, filename);
    std::cout << "Error: " << error << std::endl;
    assert(error == 0);
    auto image = make_unique<ImageBuffer>(width, height);

    auto iit = buffer.cbegin();
    auto oit = image->begin();

    while(iit != buffer.cend())
    {
        int ri = *(iit++);
        int gi = *(iit++);
        int bi = *(iit++);
        int ai = *(iit++);
        double d = 1/255.0;
        double r = ri * d;
        double g = gi * d;
        double b = bi * d;
        double a = ai * d;
        *(oit++) = Color(r, g, b, a);
    }
    return image;
}
