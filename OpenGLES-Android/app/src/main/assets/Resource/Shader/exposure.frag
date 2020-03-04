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
//uniform
uniform sampler2D u_texture;
uniform float u_exposure;
///////////////////////////////////////////////////////////
//varying
varying vec2 v_texCoord;

void main() {
	highp vec4 texture = texture2D(u_texture, v_texCoord);
	gl_FragColor = vec4(texture.rgb * pow(2.0, u_exposure), texture.a);
}
