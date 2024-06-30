/* vim: set filetype=glsl : */

in vec2 uv;

out vec4 final_color;

const vec3 BASE_COLOR = vec3(1.0, 1.0, 1.0);

void main() {
    final_color = vec4(BASE_COLOR, 1.0);
}
