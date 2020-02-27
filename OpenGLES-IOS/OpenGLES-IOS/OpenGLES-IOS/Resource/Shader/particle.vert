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

void main(void) {
    v_color = a_color;
    gl_PointSize = 128.0;
    vec4 position = vec4(a_position.x + a_normal.x, a_position.y + a_normal.y, a_position.z + a_normal.z, 1.0);
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * position;
}

