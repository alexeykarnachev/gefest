/* vim: set filetype=glsl : */

out vec4 final_color;

const vec3 COLOR = vec3(1.0, 1.0, 0.2);
const float ALPHA = 0.9;

void main() {
    final_color = vec4(COLOR, ALPHA);
}
