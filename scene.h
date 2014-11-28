#pragma once

#include "shape/ishape.h"
#include "intersection.h"
#include "ilightsource.h"
#include "shader/imaterial.h"
#include "shader/ishader.h"

#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <string>

class Scene
{
public:
    void add_shape(std::unique_ptr<IShape> shape)
    {
        _shapes.push_back(std::move(shape));
    }

    void add_light(std::unique_ptr<ILightSource> light)
    {
        _lights.push_back(std::move(light));
    }

    void add_shader(const std::string& name, std::unique_ptr<IShader> shader)
    {
        assert(_shaders.find(name) == _shaders.end());
        _shaders[name] = std::move(shader);
    }

    void add_material(const std::string& name, std::unique_ptr<IMaterial> material)
    {
        assert(_materials.find(name) == _materials.end());
        _materials[name] = std::move(material);
    }

    const IShader* get_shader(const std::string& name) const
    {
        std::cout << "Resolving shader: " << name << std::endl;
        const auto& it = _shaders.find(name);
        assert(it != _shaders.end());
        return it->second.get();
    }

    const IMaterial* get_material(const std::string& name) const
    {
        std::cout << "Resolving material: " << name << std::endl;
        const auto& it = _materials.find(name);
        assert(it != _materials.end());
        return it->second.get();
    }

    void initialize()
    {
        for(auto& material : _materials)
            material.second->initialize(*this);

        for(auto& shader : _shaders)
            shader.second->initialize();

        for(auto& shape : _shapes)
            shape->initialize(*this);
    }

    std::unique_ptr<Intersection> intersect(const Ray& ray) const;

    bool hit(const Ray& ray, double length) const;

    const std::vector<std::unique_ptr<ILightSource>>& lights() const
    {
        return _lights;
    }


private:
    std::vector<std::unique_ptr<IShape>> _shapes;
    std::vector<std::unique_ptr<ILightSource>> _lights;
    std::map<std::string, std::unique_ptr<IShader>> _shaders;
    std::map<std::string, std::unique_ptr<IMaterial>> _materials;

};
