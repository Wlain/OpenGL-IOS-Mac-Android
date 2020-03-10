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

uniform vec4 u_specularColor;
uniform vec4 u_specularMaterial;
uniform vec4 u_lightPosition;
uniform vec4 u_cameraPosition;
uniform float u_shininess;



///////////////////////////////////////////////////////////
//varying
varying vec2 v_texCoord;
varying vec4 v_color;

void main(void) {
    vec3 normal = normalize(mat3(u_normalMatrix) * a_normal.xyz);
    vec3 l = normalize(u_lightPosition.xyz);
    vec3 reflectDir = reflect(-l, normal);
    vec4 worldPosition = u_modelMatrix * a_position;
    vec3 viewDir = normalize(u_cameraPosition.xyz - worldPosition.xyz);
    v_color = u_specularColor * u_specularMaterial * pow(max(0.0, dot(viewDir, reflectDir)), u_shininess);
    v_texCoord = a_texCoord.st;
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}


