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
uniform vec4 u_ambientColor;
uniform vec4 u_diffuseColor;
uniform vec4 u_specularColor;
uniform vec4 u_ambientMaterial;
uniform vec4 u_diffuseMaterial;
uniform vec4 u_specularMaterial;
uniform vec4 u_lightPosition;
// 镜面反射光是跟着视点变化而变化的
uniform vec4 u_cameraPosition;
// 可选的参数
uniform vec4 u_optionalParam;

///////////////////////////////////////////////////////////
//varying
varying vec2 v_texcoord;
varying vec4 v_color;
varying vec4 v_normal;
varying vec4 v_worldPosition;


void main()
{
    vec4 color = vec4(0.0);
    // 环境光
    vec4 ambientColor = u_ambientColor * u_ambientMaterial;
    vec3 lightOrientation = normalize(u_lightPosition.xyz);;
    vec3 normal = normalize(v_normal.xyz);
    // 光线强度
    float diffuseIntensity = max(0.0, dot(lightOrientation, normal));
    // 漫反射光
    vec4 diffuseColor = u_diffuseColor * u_diffuseMaterial * diffuseIntensity;
    // 镜面反色光
    vec4 specularColor = vec4(0.0);
    if (diffuseIntensity != 0.0) {
        vec3 reflectOrientation = normalize(reflect(-lightOrientation, normal));
        vec3 viewOrientation = normalize(u_cameraPosition.xyz - v_worldPosition.xyz);
        specularColor = u_specularColor * u_specularMaterial * pow(max(0.0, dot(reflectOrientation, viewOrientation)), u_optionalParam.x);
    }
    color = ambientColor + diffuseColor + specularColor;
    gl_FragColor = color;
}
