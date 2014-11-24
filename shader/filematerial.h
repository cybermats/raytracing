#pragma once

#include "imaterial.h"
#include "../color.h"
#include "../intersection.h"

#include <memory>
#include <string>

class ImageBuffer;

class FileMaterial : public IMaterial
{
public:
    FileMaterial(const std::string& filename);

    virtual Color shade(const Intersection &intersection) const override;
    virtual void initialize(const Scene &) override {}

private:
    std::unique_ptr<ImageBuffer> _buffer;
};

