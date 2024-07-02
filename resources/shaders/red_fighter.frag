/* vim: set filetype=glsl : */

in vec3 frag_model_pos;
in vec3 frag_world_pos;
in vec2 frag_tex_coord;
in vec3 frag_normal;

uniform AmbientLight ambient_light;
uniform PointLight point_light;
uniform sampler2D texture0;

out vec4 final_color;

bool check_if_emissive(vec3 color) {
    float r = color.r;
    float g = color.g;
    float b = color.b;

    return (g >= 0.95) || (r >= 0.95);
}

void main() {
    vec3 base_color = texture(texture0, frag_tex_coord).rgb;
    bool is_emissive = check_if_emissive(base_color);

    vec3 total_color;
    if (is_emissive) {
        total_color = base_color;
    } else {
        total_color = get_total_color(
                frag_world_pos,
                frag_normal,
                base_color,
                ambient_light,
                point_light
            );
    }

    final_color = vec4(total_color, 1.0);
}
