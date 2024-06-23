/* vim: set filetype=glsl : */

in vec2 frag_tex_coord;

uniform sampler2D texture0;

out vec4 final_color;

void main() {
    vec3 color = texture(texture0, frag_tex_coord).rgb;
    final_color = vec4(color, 1.0);
}
