/* vim: set filetype=glsl : */

in vec3 vertexPosition;
in vec2 vertexTexCoord;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 mvp;

out vec2 frag_tex_coord;
out vec3 frag_model_pos;
out vec3 frag_world_pos;

void main() {
    frag_tex_coord = vertexTexCoord;
    frag_model_pos = vertexPosition;
    frag_world_pos = (matModel * vec4(frag_model_pos, 1.0)).xyz;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
