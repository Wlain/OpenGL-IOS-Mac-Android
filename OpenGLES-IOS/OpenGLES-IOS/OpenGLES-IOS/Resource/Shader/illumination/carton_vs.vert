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
    float intensity = max(0.0, dot(l, normal));
    vec4 color;
    if (intensity > 0.5)
        color = vec4(0.4, 0.4, 0.4, 1.0);
    else
        color = vec4(0.1, 0.1, 0.1, 1.0);
    v_color = color + ambientColor;
    v_texCoord = a_texCoord.st;
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}


