///////////////////////////////////////////////////////////
//attribute
attribute vec4 a_position;
//attribute vec2 a_texCoord;

///////////////////////////////////////////////////////////
//uniform
uniform mat4 u_worldViewProjectionMatrix;

///////////////////////////////////////////////////////////
//varying
//varying vec2 v_texcoord;

void main(void) {
//    v_texcoord = a_texCoord;
    gl_Position = u_worldViewProjectionMatrix * a_position;
}

