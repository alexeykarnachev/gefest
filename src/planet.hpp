#pragma once

namespace gefest {
namespace planet {

extern int N_LEVELS;
extern float FREQ_MULT;
extern float AMPL_MULT;
extern float FREQ_INIT;

void load();
void unload();

void draw();

}  // namespace planet
}  // namespace gefest
