/* vim: set filetype=glsl : */

in vec3 frag_model_pos;

uniform sampler2D texture0;

out vec4 final_color;

void main() {
    vec2 uv = sphere_to_uv(frag_model_pos);
    vec3 base_color = texture(texture0, uv).rgb;

    final_color = vec4(base_color, 1.0);
}
