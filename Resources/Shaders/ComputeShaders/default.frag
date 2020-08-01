#version 430 core 

in vec3 pass_position;
in vec3 pass_color;

out vec4 outColor;

void main()
{
	vec3 pos = normalize(pass_position);
	float r = pass_color.x
	float g = pass_color.y;
	float b = pass_color.z;

	outColor = vec4(r, g, b, 1.0);
}