///////////////////////////////////////////////////////////
//attribute
attribute vec4 a_position;
attribute vec4 a_texCoord;
attribute vec4 a_color;
attribute vec4 a_normal;
///////////////////////////////////////////////////////////
//uniform
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

///////////////////////////////////////////////////////////
//varying
varying vec4 v_color;
varying vec3 v_normal;
varying vec3 v_worldPosition;

void main(void) {
    v_color = a_color;
    v_normal = a_normal.xyz;
    v_worldPosition = (u_modelMatrix * a_position).xyz;
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}

