///////////////////////////////////////////////////////////
//attribute
attribute vec4 a_position;
//attribute vec2 a_texCoord;
attribute vec4 a_color;

///////////////////////////////////////////////////////////
//uniform
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
///////////////////////////////////////////////////////////
//varying
//varying vec2 v_texcoord;
varying vec4 v_color;

void main(void) {
    // v_texcoord = a_texCoord.xy;
    v_color = a_color;
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}

