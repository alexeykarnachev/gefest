/* vim: set filetype=glsl : */

in vec3 frag_model_pos;
in vec3 frag_world_pos;
in vec3 frag_normal;

uniform PointLight point_light;

uniform int n_levels;
uniform float freq_mult;
uniform float ampl_mult;
uniform float freq_init;

uniform float water_level;
uniform float sand_level;
uniform float grass_level;
uniform float rock_level;

out vec4 final_color;

const vec3 WATER_COLOR = vec3(0.1, 0.45, 0.6);
const vec3 SAND_COLOR = vec3(0.8, 0.7, 0.5);
const vec3 GRASS_COLOR = vec3(0.3, 0.6, 0.05);
const vec3 ROCK_COLOR = vec3(0.45, 0.4, 0.4);
const vec3 SNOW_COLOR = vec3(0.9, 0.9, 1.0);

void main() {
    float height = octave_perlin_noise(
            frag_model_pos.x,
            frag_model_pos.y,
            frag_model_pos.z,
            n_levels,
            freq_mult,
            ampl_mult,
            freq_init
        );

    // -------------------------------------------------------------------
    // base color
    vec3 base_color = vec3(1.0, 0.0, 0.0);
    if (height <= water_level) base_color = WATER_COLOR;
    else if (height <= sand_level) base_color = SAND_COLOR;
    else if (height <= grass_level) base_color = GRASS_COLOR;
    else if (height <= rock_level) base_color = ROCK_COLOR;
    else base_color = SNOW_COLOR;

    vec3 total_light = vec3(0.0, 0.0, 0.0);

    // -------------------------------------------------------------------
    // diffuse lighting
    vec3 direction = normalize(frag_world_pos - point_light.position);
    vec3 diffuse_color = get_diffuse_color(
            frag_normal,
            point_light.color,
            direction,
            point_light.intensity
        );
    float dist = distance(point_light.position, frag_world_pos);
    float attenuation = 1.0 / dot(
                point_light.attenuation,
                vec3(1.0, dist, dist * dist)
            );
    total_light += diffuse_color * attenuation;

    // -------------------------------------------------------------------
    // final color
    vec3 color = total_light * base_color;
    final_color = vec4(color, 1.0);
}
