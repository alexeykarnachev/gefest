/* vim: set filetype=glsl : */

in vec3 vertexPosition;

uniform mat4 mvp;

out vec3 frag_model_pos;

void main() {
    frag_model_pos = vertexPosition;
    vec4 pos = mvp * vec4(vertexPosition, 1.0);
    gl_Position = pos.xyww;
}
