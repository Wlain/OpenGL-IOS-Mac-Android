///////////////////////////////////////////////////////////
//attribute
attribute vec4 a_position;
attribute vec4  a_texCoord;

///////////////////////////////////////////////////////////
//uniform
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

///////////////////////////////////////////////////////////
//varying
varying vec2 v_texcoord;

void main(void) {
    v_texcoord = a_texCoord.xy;
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}

