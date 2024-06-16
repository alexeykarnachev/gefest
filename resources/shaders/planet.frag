/* vim: set filetype=glsl : */

in vec3 fragPosition;

uniform int n_levels;
uniform float freq_mult;
uniform float ampl_mult;
uniform float freq_init;

out vec4 finalColor;

void main() {
    float p = octave_perlin_noise(
            fragPosition.x,
            fragPosition.y,
            fragPosition.z,
            n_levels,
            freq_mult,
            ampl_mult,
            freq_init
        );

    finalColor = vec4(p, p, p, 1.0);
}
