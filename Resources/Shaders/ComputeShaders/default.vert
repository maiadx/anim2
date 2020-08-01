#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 velocity;
layout(location = 2) in vec3 color;
layout(location = 3) in float mass;


uniform mat4 projection;
uniform mat4 view;

out vec3 pass_position;
out vec3 pass_color;

void main()
{
    pass_scale = 1.0f;
    pass_speed = length(velocity);
    pass_position = position;
    gl_Position = projection * view * vec4(position, 1.0);
}
