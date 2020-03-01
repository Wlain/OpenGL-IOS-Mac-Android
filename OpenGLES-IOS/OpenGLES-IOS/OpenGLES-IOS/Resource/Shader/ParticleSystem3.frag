#version 300 es
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
uniform vec4 u_color;
uniform sampler2D u_texture;
///////////////////////////////////////////////////////////
// Varying
in float v_lifetime;

///////////////////////////////////////////////////////////
// Out
layout(location = 0) out vec4 fragColor;

void main() {
    vec4 texColor;
    texColor = texture(u_texture, gl_PointCoord);
    fragColor = vec4(u_color) * texColor;
    fragColor.a *= v_lifetime;
}

