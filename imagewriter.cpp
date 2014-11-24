#include "imagewriter.h"
#include "imagebuffer.h"

#include "lodepng.h"

ImageWriter::ImageWriter(std::shared_ptr<ImageBuffer> buffer)
    : _buffer(buffer)
{}


void ImageWriter::savePNG(const std::string &filename) const {
    std::vector<unsigned char> localBuffer;
    localBuffer.reserve(_buffer->width() * _buffer->height() * 4);

    for(const auto& color : *_buffer)
    {
        for(size_t i = 0; i < 4; ++i)
        {
            auto temp = color[i] * 255.0;
            auto c = std::max(0.0, std::min(255.0, temp));
            localBuffer.push_back((unsigned char)(c));
        }
    }

    unsigned int error = lodepng::encode(filename, localBuffer, _buffer->width(), _buffer->height());
    assert(error == 0);


}
