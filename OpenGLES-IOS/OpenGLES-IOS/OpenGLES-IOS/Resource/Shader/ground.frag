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
    vec4 ambientColor = u_ambientColor * u_ambientMaterial;
    vec3 lightOisition = u_lightPosition.xyz;
    vec3 LightDirection = normalize(lightOisition);
    vec3 normal = normalize(v_normal);
    float diffuseIntensity = max(0.0, dot(LightDirection, normal));
    vec4 diffuseColor = u_diffuseColor * u_diffuseMaterial * diffuseIntensity;
    color = ambientColor + diffuseColor;
    gl_FragColor = color * v_color;
}
