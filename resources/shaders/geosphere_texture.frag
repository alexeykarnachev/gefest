/* vim: set filetype=glsl : */

in vec2 uv;

out vec4 final_color;

vec3 uv_to_sphere(float u, float v, float radius) {
    float theta = u * 2.0 * PI;
    float phi = v * PI;

    float x = radius * sin(phi) * cos(theta);
    float y = radius * cos(phi);
    float z = radius * sin(phi) * sin(theta);

    return vec3(x, y, z);
}

void main() {
    vec3 pos = uv_to_sphere(uv.x, uv.y, 1.0);
    pos *= 50.0;
    float height = perlin_noise(pos.x, pos.y, pos.z);
    final_color = vec4(height, height, height, 1.0);
}
