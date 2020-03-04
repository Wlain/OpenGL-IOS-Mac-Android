///////////////////////////////////////////////////////////
//attribute
attribute vec4 a_position;
attribute vec4 a_texCoord;

///////////////////////////////////////////////////////////
//varying
varying vec2 v_texCoord;

void main(void) {
    v_texCoord = a_texCoord.xy;
    gl_Position = a_position;
}

