///////////////////////////////////////////////////////////
//attribute
attribute vec4 a_position;
attribute vec4 a_texCoord;
attribute vec4 a_color;
attribute vec4 a_normal;
///////////////////////////////////////////////////////////
//uniform
uniform mat4 u_worldViewProjectionMatrix;

///////////////////////////////////////////////////////////
//varying
varying vec2 v_texcoord;
varying vec4 v_color;

void main(void) {
    v_texcoord = a_texCoord.xy;
    v_color = a_color;
    vec4 normal = a_normal;
    gl_Position = u_worldViewProjectionMatrix * a_position;
}

