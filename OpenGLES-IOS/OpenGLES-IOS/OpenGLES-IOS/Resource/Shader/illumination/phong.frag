#ifdef GL_ES//for discriminate GLES & GL
#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif
#else
#define highp
#define mediump
#define lowp
#endif
///////////////////////////////////////////////////////////
// Uniforms
uniform sampler2D u_texture;
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
varying vec3 v_normal;
varying vec3 v_worldPosition;

void main()
{
    // ambient
    vec4 ambientColor = u_ambientColor * u_ambientMaterial;
    // diffuse
    vec3 l = normalize(u_lightPosition.xyz);
    vec4 diffuseColor = u_diffuseColor * u_diffuseMaterial * max(0.0, dot(l, v_normal));
    // specular
    vec4 texture = texture2D(u_texture, v_texCoord);
    vec3 reflectDir = reflect(-l, v_normal);
    vec3 viewDir = normalize(u_cameraPosition.xyz - v_worldPosition.xyz);
    vec4 specularColor = u_specularColor * u_specularMaterial * pow(max(0.0, dot(viewDir, reflectDir)), u_shininess);
    gl_FragColor = ambientColor + diffuseColor + specularColor;
}
