/* vim: set filetype=glsl : */

in vec3 fragPosition;

uniform int n_levels;
uniform float freq_mult;
uniform float ampl_mult;
uniform float freq_init;

uniform float water_level;
uniform float sand_level;
uniform float grass_level;
uniform float rock_level;

out vec4 finalColor;

const vec3 WATER_COLOR = vec3(0.1, 0.45, 0.6);
const vec3 SAND_COLOR = vec3(0.8, 0.7, 0.5);
const vec3 GRASS_COLOR = vec3(0.3, 0.6, 0.05);
const vec3 ROCK_COLOR = vec3(0.45, 0.4, 0.4);
const vec3 SNOW_COLOR = vec3(0.9, 0.9, 1.0);

void main() {
    float height = octave_perlin_noise(
            fragPosition.x,
            fragPosition.y,
            fragPosition.z,
            n_levels,
            freq_mult,
            ampl_mult,
            freq_init
        );

    vec3 color = vec3(1.0, 0.0, 0.0);
    if (height <= water_level) color = WATER_COLOR;
    else if (height <= sand_level) color = SAND_COLOR;
    else if (height <= grass_level) color = GRASS_COLOR;
    else if (height <= rock_level) color = ROCK_COLOR;
    else color = SNOW_COLOR;

    finalColor = vec4(color, 1.0);
}
