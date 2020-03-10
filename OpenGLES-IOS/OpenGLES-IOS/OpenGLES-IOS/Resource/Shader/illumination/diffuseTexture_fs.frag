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

uniform vec4 u_diffuseColor;
uniform vec4 u_diffuseMaterial;
uniform vec4 u_lightPosition;

///////////////////////////////////////////////////////////
//varying
varying vec2 v_texCoord;
varying vec3 v_normal;

void main()
{
    vec4 texture = texture2D(u_texture, v_texCoord);
    vec3 l = normalize(u_lightPosition.xyz);
    vec4 color = u_diffuseMaterial * u_diffuseColor * max(0.0, dot(l, v_normal));
    gl_FragColor = color;
}
