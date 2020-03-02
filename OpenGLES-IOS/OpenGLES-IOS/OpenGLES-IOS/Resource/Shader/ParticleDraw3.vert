#version 300 es

#define ATTRIBUTE_POSITION      0
#define ATTRIBUTE_VELOCITY      1
#define ATTRIBUTE_SIZE          2
#define ATTRIBUTE_CURTIME       3
#define ATTRIBUTE_LIFETIME      4

///////////////////////////////////////////////////////////
// Attribute
layout(location = ATTRIBUTE_POSITION) in vec2 a_position;
layout(location = ATTRIBUTE_VELOCITY) in vec2 a_velocity;
layout(location = ATTRIBUTE_SIZE) in float a_size;
layout(location = ATTRIBUTE_CURTIME) in float a_currenttime;
layout(location = ATTRIBUTE_LIFETIME) in float a_lifetime;

uniform float u_time;
uniform vec2 u_acceleration;

void main() {
    float deltaTime = u_time - a_currenttime;
    if (deltaTime <= a_lifetime) {
        vec2 velocity = a_velocity + deltaTime * u_acceleration;
        vec2 position = a_position + deltaTime * velocity;
        gl_Position = vec4(position, 0.0, 1.0);
        gl_PointSize = a_size * (1.0 - deltaTime / a_lifetime);
    } else {
        gl_Position = vec4(-1000.0, -1000.0, 0.0, 0.0);
        gl_PointSize = 0.0;
    }
}
