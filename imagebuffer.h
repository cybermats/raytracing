#pragma once

#include "color.h"
#include "vector.h"

#include <vector>

class ImageBuffer
{
public:
    ImageBuffer(int width, int height)
            : _resolution(width, height)
            , _buffer(_resolution.x * _resolution.y, Color(0, 0, 0, 0))
    {}

    ImageBuffer(Vec2i resolution)
            : _resolution(resolution)
            , _buffer(_resolution.x * _resolution.y, Color(0, 0, 0, 0))
    {}

    void setPixel(const Color& color, const Vec2i& pixel)
    {
        _buffer[_resolution.x * pixel.y + pixel.x] = color;
    }

    int height() const
    {
        return _resolution.y;
    }

    int width() const
    {
        return _resolution.x;
    }

    class iterator
    {
    public:
        iterator() {}

        iterator(std::vector<Color>::const_iterator it)
                : _iterator(it)
        {}

        bool operator==(const iterator& other)
        {
            return _iterator == other._iterator;
        }

        bool operator!=(const iterator& other)
        {
            return _iterator != other._iterator;
        }

        iterator& operator++()
        {
            ++_iterator;
            return *this;
        }

        const Color& operator*() const
        {
            return *_iterator;
        }

    private:
        std::vector<Color>::const_iterator _iterator;
    };

    iterator begin() const
    {
        return iterator(_buffer.begin());
    }

    iterator end() const
    {
        return iterator(_buffer.end());
    }

private:
    Vec2i _resolution;
    std::vector<Color> _buffer;
};