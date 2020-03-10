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
uniform vec4 u_ambientColor;
uniform vec4 u_ambientMaterial;

///////////////////////////////////////////////////////////
//varying
varying vec2 v_texcoord;
varying vec4 v_color;

void main(void) {
    v_texcoord = a_texCoord.xy;
    v_color = u_ambientColor * u_ambientMaterial;
   gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}


