#version 130
in vec3 vertexPosition;
in vec3 vertexColor;

out vec3 outColor;

void main()
{
    outColor = vertexColor;
    gl_Position = vec4(vertexPosition, 1.0);
}
