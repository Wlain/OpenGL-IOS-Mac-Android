#version 300 es
#define POSITION_ATTRIB 1
#define COLOR_ATTRIB 0
layout(location = POSITION_ATTRIB) in vec4 a_position;
layout(location = COLOR_ATTRIB) in vec4 a_color;
out vec4 v_color;
void main() {
    v_color = a_color;
    gl_Position = a_position;
}
