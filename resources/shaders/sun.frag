/* vim: set filetype=glsl : */

out vec4 final_color;

const vec3 emit_color = vec3(1.0, 1.0, 0.9);

void main() {
    vec3 color = emit_color;
    final_color = vec4(color, 1.0);
}
