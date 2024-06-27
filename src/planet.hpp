#pragma once

#include "raylib/raylib.h"

namespace gefest::planet {

extern Vector3 POSITION;

extern int N_LEVELS;
extern float FREQ_MULT;
extern float AMPL_MULT;
extern float FREQ_INIT;

extern float WATER_LEVEL;
extern float SAND_LEVEL;
extern float GRASS_LEVEL;
extern float ROCK_LEVEL;

void update();
void draw();

}  // namespace gefest::planet
