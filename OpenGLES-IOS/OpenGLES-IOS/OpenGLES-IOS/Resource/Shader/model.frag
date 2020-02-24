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
//uniform sampler2D u_texture;
//uniform sampler2D u_diffuseTexture;
//uniform sampler2D u_mask;


///////////////////////////////////////////////////////////
//varying
varying vec2 v_texcoord;
varying vec4 v_color;

void main()
{
//    vec4 texture = texture2D(u_texture, v_texcoord);
//    vec4 diffuseTexture = texture2D(u_diffuseTexture, v_texcoord);
//    float alpha = texture2D(u_mask, v_texcoord).r;
//    gl_FragColor = vec4(mix(texture.rgb, diffuseTexture.rbg, alpha), 1.0);
    gl_FragColor = vec4(1.0);
}
