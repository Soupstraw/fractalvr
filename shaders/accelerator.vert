#version 410
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 project;
uniform vec2 screenSize;
uniform int kernelSize;
uniform sampler2D inputTex;
layout(location = 0) in vec4 position;
out mat4 vViewMatrix;
out mat4 vProjectionMatrix;
out vec4 vProject;
out vec2 vScreenSize;
out int vKernelSize;
//out sampler2D vInputTex;
void main()
{
    vViewMatrix = viewMatrix;
    vProjectionMatrix = projectionMatrix;
    vScreenSize = screenSize;
    vProject = project;
    vKernelSize = kernelSize;
    gl_Position = vec4(position.xy, 0.0, 1.0);
//	vInputTex = inputTex;
}