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
//uniform sampler2D u_diffuseTexture;

///////////////////////////////////////////////////////////
//varying
//varying vec2 v_texcoord;
varying vec4 v_color;

void main()
{
//    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    gl_FragColor = v_color;
//    gl_FragColor = texture2D(u_diffuseTexture, v_texcoord);
}
