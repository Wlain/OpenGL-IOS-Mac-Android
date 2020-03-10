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
uniform mat4 u_normalMatrix;

uniform vec4 u_diffuseColor;
uniform vec4 u_diffuseMaterial;
uniform vec4 u_lightPosition;


///////////////////////////////////////////////////////////
//varying
varying vec2 v_texCoord;
varying vec4 v_color;

void main(void) {
    vec3 normal = mat3(u_normalMatrix) * a_normal.xyz;
    vec3 l = normalize(u_lightPosition.xyz);
    v_color = u_diffuseMaterial * u_diffuseColor * max(0.0, dot(l, normal.xyz));
    v_texCoord = a_texCoord.xy;
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}


