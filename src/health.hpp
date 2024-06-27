#pragma once

#include "entt/entity/fwd.hpp"
namespace gefest::health {

class Health {
private:
    entt::entity entity;

    float max_val;
    float current_val = max_val;

public:
    Health(entt::entity entity, float max_val);

    bool is_dead();
    void receive_damage(float val);

    void update();
};

}  // namespace gefest::health
