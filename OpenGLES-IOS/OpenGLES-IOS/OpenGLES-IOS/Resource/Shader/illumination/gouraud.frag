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

///////////////////////////////////////////////////////////
//varying
varying vec2 v_texCoord;
varying vec4 v_color;


void main()
{
    vec4 texture = texture2D(u_texture, v_texCoord);
    gl_FragColor = v_color;
}
