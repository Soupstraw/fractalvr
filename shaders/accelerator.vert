#version 410

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec2 screenSize;

layout(location = 0) in vec4 position;

out mat4 vViewMatrix;
out mat4 vProjectionMatrix;
out vec3 vRayDir;
out vec2 vScreenSize;
out vec2 vScreenPos;
out vec2 vPosition;

void main()
{
    vViewMatrix = viewMatrix;
    vProjectionMatrix = projectionMatrix;
    vScreenSize = screenSize;
    mat4 rayMat = mat4(1);
    rayMat[3] = vec4(position.xy, 0, 1);
    vRayDir = normalize(mat3(inverse(vViewMatrix))*(inverse(vProjectionMatrix) * rayMat)[3].xyz);
    gl_Position = vec4(position.xy, 0.0, 1.0);
    vScreenPos = (position.xy+1) * screenSize;
    vPosition = (position.xy+1)/2;
}