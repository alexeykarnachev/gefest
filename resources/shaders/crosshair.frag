/* vim: set filetype=glsl : */

in vec2 frag_tex_coord;

uniform float thickness;

out vec4 final_color;

void main() {
    vec2 pos = frag_tex_coord * 2.0 - 1.0;

    vec3 color = vec3(pos.x, pos.y, thickness);
    final_color = vec4(color, 0.7);
}
