#include "filematerial.h"

#include "../imagebuffer.h"
#include "../imagereader.h"

FileMaterial::FileMaterial(const std::string &filename) {
    _buffer = ImageReader::readPNG(filename);
}

Color FileMaterial::shade(const Intersection &intersection) const {
    Vec2d uv = intersection.uv();
    double u = fmod(uv.x, 1);
    double v = fmod(uv.y, 1);
    while(u < 0) u += 1;
    while(v < 0) v += 1;
    while(u >= 1) u -= 1;
    while(v >= 1) v -= 1;
    auto x = (unsigned short)(u * _buffer->width());
    auto y = (unsigned short)(v * _buffer->height());
    if(x < 0) x = 0;
    if(x >= _buffer->width()) x = _buffer->width() - 1;
    if(y < 0) y = 0;
    if(y >= _buffer->height()) x = _buffer->height() - 1;
    return (*_buffer)(x, y);
}
