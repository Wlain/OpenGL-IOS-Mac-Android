#version 300 core
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
uniform sampler2D u_bumpTexture;
uniform vec4 u_specularColor;
uniform vec4 u_specularMaterial;
uniform vec4 u_ambientColor;
uniform vec4 u_ambientMaterial;
uniform vec4 u_diffuseColor;
uniform vec4 u_diffuseMaterial;
uniform float u_shininess;

///////////////////////////////////////////////////////////
//in
in vec2 v_texCoord;
in float v_lightDistance;
in vec3 v_tangentWorldPosition;
in vec3 v_tangentLightPosition;
in vec3 v_tangentCameraPosition;

///////////////////////////////////////////////////////////
//out
out vec4 fragColor;


//light attribute
const float constantFactor = 0.5;
const float linearFactor = 0.3;
const float expFactor = 0.1;

void main()
{
    vec3 normal = texture(u_bumpTexture, v_texCoord).rgb;
    vec4 diffuseTexture = texture(u_texture, v_texCoord);
    normal = normal * 2.0 - 1.0;
    normal = normalize(normal);
   
    // 衰减因子
    float attenuation = 1.0 / (constantFactor + linearFactor * v_lightDistance + expFactor * v_lightDistance * v_lightDistance);
    // ambient
    vec4 ambientColor = u_ambientColor * u_ambientMaterial;
    // diffuse
    vec3 l = normalize(v_tangentLightPosition - v_tangentWorldPosition);
    vec4 diffuseColor = u_diffuseColor * u_diffuseMaterial * max(0.0, dot(l, normal));
    // specular
    
    vec3 reflectDir = reflect(l, normal);
    vec3 viewDir = normalize(v_tangentCameraPosition.xyz - v_tangentWorldPosition.xyz);
    vec4 specularColor = u_specularColor * u_specularMaterial * pow(max(0.0, dot(viewDir, reflectDir)), u_shininess);
    fragColor = (ambientColor + diffuseColor + specularColor) * diffuseTexture;
}
