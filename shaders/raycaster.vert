#version 410
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 project;
uniform vec2 screenSize;
layout(location = 0) in vec4 position;
out mat4 vViewMatrix;
out mat4 vProjectionMatrix;
out vec4 vProject;
out vec2 vScreenSize;
out vec4 vWorldPos;
void main()
{
    vViewMatrix = inverse(viewMatrix);
    mat4 rotScaleMatrix = vViewMatrix;
    rotScaleMatrix[3] = vec4(0);
    vProjectionMatrix = rotScaleMatrix * inverse(projectionMatrix);
    vScreenSize = screenSize;
    vProject = project;
    vWorldPos = vViewMatrix * vec4(0,0,0,1);
    gl_Position = vec4(position.xy, 0.0, 1.0);
}