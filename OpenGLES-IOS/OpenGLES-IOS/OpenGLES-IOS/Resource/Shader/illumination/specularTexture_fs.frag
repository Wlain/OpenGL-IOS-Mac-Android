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
    vec4 texture = texture2D(u_texture, v_texCoord);
    vec3 l = normalize(u_lightPosition.xyz);
    vec3 reflectDir = reflect(-l, v_normal);
    vec3 viewDir = normalize(u_cameraPosition.xyz - v_worldPosition.xyz);
    vec4 color = u_specularColor * u_specularMaterial * pow(max(0.0, dot(viewDir, reflectDir)), u_shininess);
    gl_FragColor = color;
}
