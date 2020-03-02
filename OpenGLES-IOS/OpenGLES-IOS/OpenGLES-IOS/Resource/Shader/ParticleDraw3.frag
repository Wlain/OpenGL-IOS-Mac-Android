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
// Attribute

///////////////////////////////////////////////////////////
// Uniforms
uniform sampler2D u_texture;
uniform vec4 u_color;

///////////////////////////////////////////////////////////
// Out
layout(location = 0) out vec4 fragColor;
void main() {
    vec4 textureColor = vec4(0.0);
    textureColor = texture(u_texture, gl_PointCoord);
    fragColor = textureColor * u_color;
}

