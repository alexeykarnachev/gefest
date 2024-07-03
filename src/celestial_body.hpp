#pragma once

#include "entt/entity/fwd.hpp"

namespace gefest::celestial_body {

class CelestialBody {
private:
    const entt::entity entity;

public:
    CelestialBody(entt::entity);

    void update();
    void draw();
};

}  // namespace gefest::celestial_body
