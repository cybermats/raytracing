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

    void addPixel(const Color& color, const Vec2i& pixel)
    {
        _buffer[_resolution.x * pixel.y + pixel.x] += color;
    }

    inline Color& operator()(int x, int y)
    {
        return _buffer[_resolution.x * y + x];
    }

    inline const Color& operator()(int x, int y) const
    {
        return _buffer[_resolution.x * y + x];
    }

    int height() const
    {
        return _resolution.y;
    }

    int width() const
    {
        return _resolution.x;
    }

    class const_iterator
    {
    public:
        const_iterator() {}

        const_iterator(std::vector<Color>::const_iterator it)
                : _iterator(it)
        {}

        bool operator==(const const_iterator& other)
        {
            return _iterator == other._iterator;
        }

        bool operator!=(const const_iterator& other)
        {
            return _iterator != other._iterator;
        }

        const_iterator& operator++()
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

    class iterator
    {
    public:
        iterator() {}

        iterator(std::vector<Color>::iterator it)
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

        iterator operator++(int)
        {
            auto temp = iterator(_iterator);
            ++_iterator;
            return temp;
        }

        const Color& operator*() const
        {
            return *_iterator;
        }

        Color& operator*()
        {
            return *_iterator;
        }

    private:
        std::vector<Color>::iterator _iterator;
    };

    iterator begin()
    {
        return iterator(_buffer.begin());
    }

    const_iterator begin() const
    {
        return const_iterator(_buffer.begin());
    }

    iterator end()
    {
        return iterator(_buffer.end());
    }

    const_iterator end() const
    {
        return const_iterator(_buffer.end());
    }

private:
    Vec2i _resolution;
    std::vector<Color> _buffer;
};