#version 300 core
///////////////////////////////////////////////////////////
//in
in vec4 a_position;
in vec4 a_texCoord;
in vec4 a_normal;
in vec4 a_tangent;
in vec4 a_bitangent;

///////////////////////////////////////////////////////////
//uniform
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform vec4 u_lightPosition;
uniform vec4 u_cameraPosition;

///////////////////////////////////////////////////////////
//out
out vec2 v_texCoord;
out float v_lightDistance;
out vec3 v_tangentWorldPosition;
out vec3 v_tangentLightPosition;
out vec3 v_tangentCameraPosition;

void main(void) {
    // inverseTranspose
    mat3 normalMatrix = transpose(inverse(mat3(u_modelMatrix)));
    vec3 N = normalize(mat3(normalMatrix) * a_normal.xyz);
    vec3 T = normalize(mat3(normalMatrix) * a_tangent.xyz);
    vec3 B = cross(N, T);
    mat3 TBN = transpose(mat3(T, B, N));
    v_tangentLightPosition  = TBN * u_lightPosition.xyz;
    v_tangentCameraPosition = TBN * u_cameraPosition.xyz;
    v_tangentWorldPosition  = TBN * (u_modelMatrix * a_position).xyz;
    v_lightDistance  = length(v_tangentLightPosition.xyz - v_tangentWorldPosition.xyz);
    v_texCoord = a_texCoord.st;
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}


