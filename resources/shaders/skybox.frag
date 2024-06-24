/* vim: set filetype=glsl : */

in vec3 frag_model_pos;

uniform float stars_frequency;
uniform float stars_min_brightness;

out vec4 final_color;

void main() {
    vec3 pos = frag_model_pos * stars_frequency;
    float p = perlin_noise(pos.x, pos.y, pos.z);
    p = smoothstep(stars_min_brightness, 1.0, p);
    vec3 stars_color = vec3(p, p, p);

    vec3 color = stars_color;
    final_color = vec4(color, 1.0);
}
