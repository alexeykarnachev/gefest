/* vim: set filetype=glsl : */

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

uniform mat4 matModel;
uniform mat4 mvp;

out vec3 frag_model_pos;
out vec3 frag_world_pos;
out vec2 frag_tex_coord;
out vec3 frag_normal;

void main() {
    frag_model_pos = vertexPosition;
    frag_world_pos = (matModel * vec4(frag_model_pos, 1.0)).xyz;
    frag_tex_coord = vertexTexCoord;

    mat3 matNormal = transpose(inverse(mat3(matModel)));
    frag_normal = normalize(matNormal * vertexNormal);

    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
