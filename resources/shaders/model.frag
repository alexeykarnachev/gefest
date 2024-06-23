/* vim: set filetype=glsl : */

out vec4 final_color;

void main() {
    vec3 color = vec3(0.5, 0.9, 0.7);
    final_color = vec4(color, 1.0);
}
