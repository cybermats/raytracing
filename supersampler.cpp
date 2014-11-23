#include "supersampler.h"
#include <random>

std::vector<Ray> SuperSampler::generate(const std::vector<Ray>& rays) const {

    std::vector<Ray> output;
    output.reserve(rays.size() * _amount * _amount);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1, 1);

    for(const auto& ray : rays)
    {
        auto dU = ray.dU();
        auto dV = ray.dV();
        auto ddU = dU / _amount;
        auto ddV = dV / _amount;
        auto sideStart = ray.direction() - dU - dV + ddU + ddV;
        for(size_t v = 0; v < _amount; ++v)
        {
            auto position = sideStart;
            for(size_t u = 0; u < _amount; ++u)
            {
                Vec3d direction(position);
                if(_randomize)
                    direction +=  (dis(gen) * ddU + dis(gen) * ddV);

                Ray subRay(ray.origin(), normalize(direction), ray.pixel(), dU, dV, ray.importance()/(_amount*_amount));
                output.push_back(subRay);
                position += (2 * ddU);
            }
            sideStart += (2 * ddV);
        }
    }
    return output;
}
