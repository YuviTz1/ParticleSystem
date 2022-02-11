#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aOffset;
out vec3 fColor;
void main()
{
	gl_Position = vec4(aPos + aOffset,1.0);
	fColor = vec3(1.0f, 1.0f, 1.0f);
}