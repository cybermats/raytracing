#pragma once

#include <stddef.h>
#include <vector>
#include "vector.h"
#include "ray.h"

class SuperSampler
{
public:
    SuperSampler(size_t amount, bool randomize = false)
            : _amount(amount)
            , _randomize(randomize)
    {
    }

    std::vector<Ray> generate(const std::vector<Ray>& rays) const;
private:
    size_t _amount;
    bool _randomize;

};
