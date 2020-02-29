#version 300 es
#define POSITION_ATTRIB 0
layout(location = POSITION_ATTRIB) in vec4 a_position;
void main() {
    gl_Position = a_position;
}
