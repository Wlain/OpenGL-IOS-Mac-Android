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
uniform vec4 u_ambientColor;
uniform vec4 u_ambientMaterial;
uniform vec4 u_diffuseColor;
uniform vec4 u_diffuseMaterial;
uniform vec4 u_lightPosition;
uniform vec4 u_cameraPosition;
uniform float u_shininess;

///////////////////////////////////////////////////////////
//varying
varying vec2 v_texCoord;
varying vec4 v_color;

void main(void) {
    vec3 normal = normalize(mat3(u_normalMatrix) * a_normal.xyz);
    vec3 worldPosition = (u_modelMatrix * a_position).xyz;
    // ambient
    vec4 ambientColor = u_ambientColor * u_ambientMaterial;
    // diffuse
    vec3 l = normalize(u_lightPosition.xyz);
    vec4 diffuseColor = u_diffuseColor * u_diffuseMaterial * max(0.0, dot(l, normal));
    // specular
    vec3 reflectDir = reflect(-l, normal);
    vec3 viewDir = normalize(u_cameraPosition.xyz - worldPosition.xyz);
    vec4 specularColor = u_specularColor * u_specularMaterial * pow(max(0.0, dot(viewDir, reflectDir)), u_shininess);
    v_color = ambientColor + diffuseColor + specularColor;
    v_texCoord = a_texCoord.st;
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}


