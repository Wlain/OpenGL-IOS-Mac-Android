#version 300 es
#define NUM_PARTICLES           200
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

///////////////////////////////////////////////////////////
// Unfiorm
// u_time：发射时间
uniform float u_time;
uniform float u_emissionRate; // 粒子发射率
uniform mediump sampler3D s_noiseTexture;

///////////////////////////////////////////////////////////
// Varying
out vec2 v_position;
out vec2 v_velocity;
out float v_size;
out float v_currenttime;
out float v_lifetime;
out vec4 v_randomColor;

float random(float n) {
    // fract(x), 返回x的小数部分数据
    return fract(sin(n) * 43758.5453123) * 0.5;
}

float randomValue(inout float seed) {
   float vertexId = float( gl_VertexID ) / float( NUM_PARTICLES );
   vec3 texCoord = vec3(u_time, vertexId, seed);
   seed += 0.1;
   return texture(s_noiseTexture, texCoord).r;
}

void main() {
    float seed = u_time;
    float lifetime = a_currenttime - u_time;
    if(lifetime <= 0.0 && randomValue(seed) < u_emissionRate) {
        v_position = vec2(0.0, 0.0);
        v_velocity = vec2(randomValue(seed) * 2.0 - 1.0,
                          randomValue(seed) * 1.4 + 1.0);
        v_size = randomValue(seed) * 20.0 + 60.0;
        v_currenttime = u_time;
        v_lifetime = 4.0;
    } else {
        v_position = a_position;
        v_velocity = a_velocity;
        v_size = a_size;
        v_currenttime = a_currenttime;
        v_lifetime = a_lifetime;
    }
    v_randomColor = vec4(1.0, 1.0, 1.0, 1.0);
    gl_Position = vec4(v_position, 0.0, 1.0);
}





