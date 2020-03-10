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
uniform vec4 u_ambientMaterial;

///////////////////////////////////////////////////////////
//varying
varying vec2 v_texcoord;

void main()
{
    vec4 texture = texture2D(u_texture, v_texcoord);
    gl_FragColor = u_ambientColor * u_ambientMaterial;;
}
