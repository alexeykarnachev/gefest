/* vim: set filetype=glsl : */

in vec3 frag_model_pos;

uniform float stars_frequency;
uniform float stars_min_brightness;

uniform float nebula_frequency;
uniform float nebula_min_brightness;

out vec4 final_color;

const vec3 NEBULA_COLOR = vec3(0.15, 0.0, 0.1);

void main() {
    // stars
    vec3 pos = frag_model_pos * stars_frequency;
    float p = perlin_noise(pos.x, pos.y, pos.z);
    p = smoothstep(stars_min_brightness, 1.0, p);
    vec3 stars_color = vec3(p, p, p);

    // nebula
    pos = frag_model_pos * nebula_frequency;
    p = perlin_noise(pos.x, pos.y, pos.z);
    p = smoothstep(nebula_min_brightness, 1.0, p);
    vec3 nebula_color = p * NEBULA_COLOR;

    // final color
    vec3 color = stars_color + nebula_color;
    final_color = vec4(color, 1.0);
}
