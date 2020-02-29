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
layout(location = 0) out vec4 fragColor0;
layout(location = 1) out vec4 fragColor1;
layout(location = 2) out vec4 fragColor2;
layout(location = 3) out vec4 fragColor3;
void main()
{
   // first buffer will contain red color
    fragColor0 = vec4 ( 1.0, 0.0, 0.0, 1.0 );
                                
    // second buffer will contain green color
    fragColor1 = vec4 ( 0.0, 1.0, 0.0, 1.0 );
                                
    // third buffer will contain blue color
    fragColor2 = vec4 ( 0.0, 0.0, 1.0, 1.0 );
                                
    // fourth buffer will contain gray color
    fragColor3 = vec4 ( 0.5, 0.5, 0.5, 1.0 );
}
