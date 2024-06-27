#include "health.hpp"

#include "registry.hpp"
#include <algorithm>

namespace gefest::health {

Health::Health(entt::entity entity, float max_val)
    : entity(entity)
    , max_val(max_val) {}

bool Health::is_dead() {
    return this->current_val <= 0.0;
}

void Health::receive_damage(float val) {
    this->current_val -= val;
}

void Health::update() {
    this->current_val = std::clamp(this->current_val, 0.0f, this->max_val);

    if (this->is_dead()) {
        registry::registry.destroy(this->entity);
    }
}

}  // namespace gefest::health
