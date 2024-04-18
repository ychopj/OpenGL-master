#version 450 core
layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 centerLine; // Center line position

out vec3 centerDist; // Distance to center line
void main() {
    gl_Position = projection * view * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    centerDist = abs(aPos - centerLine);
}