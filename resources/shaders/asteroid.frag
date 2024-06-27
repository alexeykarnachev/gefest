/* vim: set filetype=glsl : */

in vec3 frag_normal;

uniform vec3 sun_position;

out vec4 final_color;

const vec3 diffuse_color = vec3(0.1, 0.05, 0.1);

void main() {
    vec3 color = diffuse_color;
    final_color = vec4(color, 1.0);
}
