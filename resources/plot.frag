#version 330 core

out vec4 fragColor;

uniform vec4 u_pColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);

void main()
{
    fragColor = u_pColor;
}
