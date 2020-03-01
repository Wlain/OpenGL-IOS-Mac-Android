#version 300 es
#define ATTRIBUTE_LIFETIME_LOCATION       0
#define ATTRIBUTE_STARTPOSITION_LOCATION  1
#define ATTRIBUTE_ENDPOSITION_LOCATION    2
///////////////////////////////////////////////////////////
// Attribute
layout(location = ATTRIBUTE_LIFETIME_LOCATION) in float a_lifetime;
layout(location = ATTRIBUTE_STARTPOSITION_LOCATION) in vec3 a_startPosition;
layout(location = ATTRIBUTE_ENDPOSITION_LOCATION) in vec3 a_endPosition;

///////////////////////////////////////////////////////////
// Uniforms
uniform float u_time;
uniform vec3 u_centerPosition;

///////////////////////////////////////////////////////////
// Out
out float v_lifetime;

void main() {
    if(u_time < a_lifetime) {
        gl_Position.xyz = a_startPosition + (u_time * a_endPosition);
        gl_Position.xyz += u_centerPosition;
        gl_Position.w = 1.0;
    } else {
        // 屏幕之外会被裁剪
        gl_Position = vec4(-1000.0, -1000.0, 0.0, 0.0);
    }
    v_lifetime = 1.0 - (u_time / a_lifetime);
    v_lifetime = clamp(v_lifetime, 0.0, 1.0);
    gl_PointSize = (v_lifetime * v_lifetime) * 40.0;
}



