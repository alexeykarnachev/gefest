/* vim: set filetype=glsl : */

in vec3 vertexPosition;

out vec2 uv;

void main() {
    uv = vertexPosition.xy;
    gl_Position = vec4(vertexPosition.xy * 2.0 - 1.0, 0.0, 1.0);
}

