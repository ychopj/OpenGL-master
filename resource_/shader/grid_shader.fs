#version 450 core
in vec3 centerDist;

out vec4 FragColor;

void main() {
    if (centerDist.x < 0.01 )
    {
        FragColor = vec4(0.5f, 0.75f, 0.75f, 1.0f); // Center line color
    }
    else if( centerDist.z < 0.01)
    {
        FragColor = vec4(0.75f, 0.5f, 0.5f, 1.0f);
    }
    else
    {
        FragColor = vec4(0.25f, 0.25f, 0.25f, 1.0f); // Other lines color
    }
}