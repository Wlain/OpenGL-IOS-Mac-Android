///////////////////////////////////////////////////////////
//attribute
attribute vec4 a_position;
attribute vec2 a_texCoord;
//attribute vec4 a_color;
///////////////////////////////////////////////////////////
//uniform
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat2 u_rotation; 
uniform vec2 u_flipScale; 

///////////////////////////////////////////////////////////
//varying
varying vec2 v_texCoord;


void main(void) {
	vec4 position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;

	v_texCoord = u_flipScale * (a_position.xy / 2.0 * u_rotation) + 0.5;
	
    gl_Position = position;
}

