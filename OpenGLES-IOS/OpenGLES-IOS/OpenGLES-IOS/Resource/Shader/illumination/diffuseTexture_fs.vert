///////////////////////////////////////////////////////////
//attribute
attribute vec4 a_position;
attribute vec4 a_texCoord;
attribute vec4 a_normal;

///////////////////////////////////////////////////////////
//uniform
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_normalMatrix;

///////////////////////////////////////////////////////////
//varying
varying vec2 v_texCoord;
varying vec3 v_normal;

void main(void) {
    vec3 normal = normalize(mat3(u_normalMatrix) * a_normal.xyz);
    v_normal = normal;
    v_texCoord = a_texCoord.xy;
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}


