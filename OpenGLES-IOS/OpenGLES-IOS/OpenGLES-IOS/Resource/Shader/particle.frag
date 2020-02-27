#version 100 // 点精灵的版本限制
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
varying vec4 v_color;

void main()
{
    if (length(gl_PointCoord - vec2(0.5)) > 0.5)
        discard;
    gl_FragColor = texture2D(u_texture, gl_PointCoord.xy) * v_color;
}
 
