/* vim: set filetype=glsl : */

in vec2 frag_tex_coord;

uniform float thickness;

out vec4 final_color;

const vec3 COLOR = vec3(0.0, 1.0, 0.0);
const float ALPHA = 0.6;

void main() {
    vec2 pos = frag_tex_coord * 2.0 - 1.0;

    float d = length(pos);
    if (d > 1.0 || d < (1.0 - thickness)) discard;

    final_color = vec4(COLOR, ALPHA);
}
