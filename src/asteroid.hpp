#pragma once

#include "entt/entity/fwd.hpp"
namespace gefest::asteroid {

class Asteroid {
private:
    entt::entity entity;

public:
    Asteroid(entt::entity entity);

    void update();
};

}  // namespace gefest::asteroid
