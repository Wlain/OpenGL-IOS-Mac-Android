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
uniform mat4 u_inverseTransposeMatrix;

///////////////////////////////////////////////////////////
//varying
varying vec2 v_texcoord;
varying vec4 v_color;
varying vec4 v_normal;
varying vec4 v_worldPosition;

void main(void) {
    v_texcoord = a_texCoord.xy;
    v_color = a_color;
    v_normal = u_inverseTransposeMatrix * a_normal;
    v_worldPosition = u_modelMatrix * a_position;
   gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}

