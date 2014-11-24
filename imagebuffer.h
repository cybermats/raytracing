#pragma once

#include "color.h"
#include "vector.h"

#include <vector>

class ImageBuffer
{
public:
    ImageBuffer(unsigned short width, unsigned short height)
            : _buffer(width * height, Color(0, 0, 0, 0))
            , _resolution(width, height)
    {}

    ImageBuffer(Vec2us resolution)
            : _buffer(resolution.x * resolution.y, Color(0, 0, 0, 0))
            , _resolution(resolution)
    {}

    void setPixel(const Color& color, const Vec2us& pixel)
    {
        _buffer[_resolution.x * pixel.y + pixel.x] = color;
    }

    void addPixel(const Color& color, const Vec2us& pixel)
    {
        _buffer[_resolution.x * pixel.y + pixel.x] += color;
    }

    inline Color& operator()(unsigned short x, unsigned short y)
    {
        return _buffer[_resolution.x * y + x];
    }

    inline const Color& operator()(unsigned short x, unsigned short y) const
    {
        return _buffer[_resolution.x * y + x];
    }

    unsigned short height() const
    {
        return _resolution.y;
    }

    unsigned short width() const
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
    std::vector<Color> _buffer;
    Vec2us _resolution;
};
