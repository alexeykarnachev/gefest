/* vim: set filetype=glsl : */

in vec3 frag_world_pos;

uniform float length;
uniform float attenuation;
uniform float start_alpha;
uniform vec3 start_position;

out vec4 final_color;

const vec3 COLOR = vec3(0.0, 1.0, 0.0);

void main() {
    float dist = distance(start_position, frag_world_pos);
    float alpha = lerp(start_alpha, 1.0, dist / length);
    alpha = pow(alpha, attenuation);

    final_color = vec4(COLOR, alpha);
}
