/* vim: set filetype=glsl : */

in vec3 frag_model_pos;
in vec3 frag_world_pos;
in vec3 frag_normal;

uniform AmbientLight ambient_light;
uniform PointLight point_light;
uniform sampler2D texture0;

out vec4 final_color;

void main() {
    vec2 uv = sphere_to_uv(frag_model_pos);
    vec3 base_color = texture(texture0, uv).rgb;
    vec3 total_color = get_total_color(
            frag_world_pos,
            frag_normal,
            base_color,
            ambient_light,
            point_light
        );

    final_color = vec4(total_color, 1.0);
}
