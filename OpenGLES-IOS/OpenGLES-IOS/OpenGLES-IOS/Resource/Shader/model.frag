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
uniform vec4 u_ambientMaterial;
uniform vec4 u_diffuseMaterial;
uniform vec4 u_lightPosition;


///////////////////////////////////////////////////////////
//varying
varying vec2 v_texcoord;
varying vec4 v_color;
varying vec4 v_normal;


void main()
{
    vec4 color = vec4(0.0);
    vec4 ambientColor = u_ambientColor * u_ambientMaterial;
    vec3 lightPosition = normalize(u_lightPosition.xyz);;
    vec3 normal = normalize(v_normal.xyz);
    // 光线强度
    float diffuseIntensity = max(0.0, dot(lightPosition, normal));
    vec4 diffuseColor = u_diffuseColor * u_diffuseMaterial * diffuseIntensity;
    color = diffuseColor + ambientColor;
    gl_FragColor = color;
}
