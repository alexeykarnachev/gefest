/* vim: set filetype=glsl : */

in vec3 fragPosition;

out vec4 finalColor;

void main() {
    int n_levels = 8;
    float freq_mult = 2.0;
    float ampl_mult = 0.5;
    float freq_init = 1.0;
    float p = octave_perlin_noise(
            fragPosition.x,
            fragPosition.y,
            fragPosition.z,
            n_levels,
            freq_mult,
            ampl_mult,
            freq_mult
        );

    finalColor = vec4(p, p, p, 1.0);
}
