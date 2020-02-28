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
uniform vec4 u_ambientColor;
uniform vec4 u_diffuseColor;
uniform vec4 u_ambientMaterial;
uniform vec4 u_diffuseMaterial;
uniform vec4 u_lightPosition;

///////////////////////////////////////////////////////////
//varying
varying vec4 v_color;
varying vec3 v_normal;
varying vec3 v_worldPosition;

void main()
{
    vec4 color = vec4(1.0);
    float distance = 0.0; // 接受光的点距离光源的距离
    float constanceFactor = 1.0;
    float linearFactor = 2.0;
    float quadricFactor = 3.0;
    vec4 ambientColor = u_ambientColor * u_ambientMaterial;
    vec3 lightDirection = v_worldPosition - u_lightPosition.xyz;
    distance = length(lightDirection);
    float attenuation = 1.0 / (constanceFactor + linearFactor * distance + quadricFactor * quadricFactor * distance);
    lightDirection = normalize(lightDirection);
    vec3 normal = normalize(v_normal);
    float diffuseIntensity = max(0.0, dot(lightDirection, normal));
    vec4 diffuseColor = u_diffuseColor * u_diffuseMaterial * diffuseIntensity * attenuation * 4.0;
    color = ambientColor + diffuseColor;
    gl_FragColor = color * v_color;
}
