#pragma once

#include "entt/entity/fwd.hpp"

namespace gefest::celestial_body {

enum class Type {
    SUN,
    PLANET,
    ASTEROID,
};

struct Sun {};

struct Planet {};

struct Asteroid {};

class CelestialBody {
private:
    const entt::entity entity;

    const Type type;

    union {
        Sun sun;
        Planet planet;
        Asteroid asteroid;
    };

public:
    CelestialBody(entt::entity, Sun sun);
    CelestialBody(entt::entity, Planet planet);
    CelestialBody(entt::entity, Asteroid asteroid);

    void draw();
};

}  // namespace gefest::celestial_body
