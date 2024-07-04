#include "raylib/raylib.h"

namespace gefest::constants {

static constexpr Vector3 FORWARD = {0.0, 0.0, -1.0};
static constexpr Vector3 RIGHT = {1.0, 0.0, 0.0};
static constexpr Vector3 UP = {0.0, 1.0, 0.0};

static constexpr float ORIGIN_UPDATE_DISTANCE = 1000.0;

extern const float SCALE;
extern const float DT;

}  // namespace gefest::constants
