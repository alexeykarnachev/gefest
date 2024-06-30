#pragma once

namespace gefest::skybox {

extern float STARS_FREQUENCY;
extern float STARS_MIN_BRIGHTNESS;

extern float NEBULA_FREQUENCY;
extern float NEBULA_MIN_BRIGHTNESS;

void generate();

void draw();

}  // namespace gefest::skybox
