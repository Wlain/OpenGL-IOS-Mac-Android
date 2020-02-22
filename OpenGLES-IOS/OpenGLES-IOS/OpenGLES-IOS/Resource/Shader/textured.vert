///////////////////////////////////////////////////////////
//attribute
attribute vec4 a_position;
//attribute vec2 a_texCoord;

///////////////////////////////////////////////////////////
//uniform
uniform mat4 u_worldViewProjectionMatrix;
uniform vec4 u_color;
///////////////////////////////////////////////////////////
//varying
//varying vec2 v_texcoord;
varying vec4 v_color;

void main(void) {
//    v_texcoord = a_texCoord;
    v_color = u_color;
    gl_Position = u_worldViewProjectionMatrix * a_position;
}

