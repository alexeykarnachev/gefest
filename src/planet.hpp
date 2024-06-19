#pragma once

#include "raylib/raylib.h"

namespace gefest {
namespace planet {

extern Vector3 PLANET_POSITION;

extern int N_LEVELS;
extern float FREQ_MULT;
extern float AMPL_MULT;
extern float FREQ_INIT;

extern float WATER_LEVEL;
extern float SAND_LEVEL;
extern float GRASS_LEVEL;
extern float ROCK_LEVEL;

extern float ATMOSPHERE_SCALE;
extern float ATMOSPHERE_ALPHA;

void load();
void unload();

void update();
void draw();

}  // namespace planet
}  // namespace gefest
