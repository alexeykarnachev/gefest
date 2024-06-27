/* vim: set filetype=glsl : */

in vec4 frag_color;
in vec2 frag_tex_coord;

uniform sampler2D texture0;

out vec4 final_color;

void main() {
    vec4 tex_color = texture(texture0, frag_tex_coord);

    vec3 color = (tex_color * frag_color).rgb;
    final_color = vec4(color, 1.0);
    final_color = frag_color;
}
