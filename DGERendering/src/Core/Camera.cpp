
#include "DGERendering/Core/Camera.h"

DGERendering::Core::Camera::Camera(glm::vec3 position, glm::vec3 up)
    : MovementSpeed(SPEED_R), MouseSensitivity(SENSITIVITY_R), Zoom(ZOOM_R)
{
    Position = position;
    WorldUp = up;
    Center = glm::vec3(0.0f, 0.0f, 0.0f);
    updateCameraVectors();
}

DGERendering::Core::Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ)
    : MovementSpeed(SPEED_R), MouseSensitivity(SENSITIVITY_R), Zoom(ZOOM_R)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Center = glm::vec3(0.0f, 0.0f, 0.0f);
    updateCameraVectors();
}

std::pair<glm::mat4, glm::mat4> DGERendering::Core::Camera::GetViewMatrix()
{
    return std::make_pair(glm::lookAt(Position, Center, Up), m_Projection);
}

void DGERendering::Core::Camera::Update(Shader* p_shader)
{
    glm::mat4 model{1.0f};

    p_shader->Set("model", model);
    p_shader->Set("view", glm::lookAt(Position, Center, Up));
    p_shader->Set("projection", m_Projection);
    p_shader->Set("viewPos", Position);
}

void DGERendering::Core::Camera::Move(Camera_Movement direction, float delta)
{
    float     velocity = MovementSpeed * delta;
    glm::vec3 deltaPos;
    if (direction == Camera_Movement::FORWARD)
        deltaPos = Front * velocity;
    if (direction == Camera_Movement::BACKWARD)
        deltaPos = -Front * velocity;
    if (direction == Camera_Movement::LEFT)
        deltaPos = -Right * velocity;
    if (direction == Camera_Movement::RIGHT)
        deltaPos = Right * velocity;
    if (direction == Camera_Movement::UP)
        deltaPos = Up * velocity;
    if (direction == Camera_Movement::DOWN)
        deltaPos = -Up * velocity;

    Position += deltaPos;
    Center += deltaPos;
    updateCameraVectors();
}

void DGERendering::Core::Camera::RotateLeft(float angle)
{
    glm::vec3 target = Position - Center;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, Up);
    glm::vec3 newPosition = glm::vec3(rotationMatrix * glm::vec4(target, 1.0f)) + Center;
    Position = newPosition;
    updateCameraVectors();
}

void DGERendering::Core::Camera::RotateUp(float angle)
{
    glm::vec3 target = Position - Center;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -angle, Right);
    glm::vec3 newPosition = glm::vec3(rotationMatrix * glm::vec4(target, 1.0f)) + Center;
    float     dot = fabsf(glm::dot(glm::normalize(newPosition), WorldUp));
    if (dot < 0.98)
        Position = newPosition;
    updateCameraVectors();
}

void DGERendering::Core::Camera::ProcessMouseScroll(float yoffset)
{
    glm::vec3 deltaPos;
    deltaPos = Front * yoffset;
    Position += deltaPos;
    Center += deltaPos;
    updateCameraVectors();
}

void DGERendering::Core::Camera::Update(int p_width, int p_height)
{
    m_Projection = glm::perspective(glm::radians(Zoom), static_cast<float>(p_width) / p_height, 0.1f, 100.0f);
}

void DGERendering::Core::Camera::updateCameraVectors()
{
    MovementSpeed = blend(0.058f, 0.258f, glm::length(Position) / 18.);
    glm::vec3 front;
    front = Center - Position;
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
