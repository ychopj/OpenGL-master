#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utility>
#include "DGERendering/Core/Shader.h"
namespace DGERendering::Core
{
#define M_PI_2 1.57079632679489661923 // pi/2

    // Defines several possible options for camera movement. Used as abstraction to stay away from
    // window-system specific input methods
    enum class Camera_Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    // Default camera values
    const float SPEED_R = 3.0f;
    const float SENSITIVITY_R = 0.0025f;
    const float ZOOM_R = 45.0f;

    class Camera
    {
    public:
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
        Camera(float posX, float posY, float posZ, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f);
        std::pair<glm::mat4, glm::mat4> GetViewMatrix();

        void Update(Shader* p_shader);
        void Move(Camera_Movement p_direction, float p_delta);
        void RotateLeft(float p_angle);
        void RotateUp(float p_angle);
        void ProcessMouseScroll(float p_yoffset);

        void Update(int, int);

    private:
        inline float blend(float h1, float h2, float alpha, float power = 1.0)
        {
            alpha = alpha < 0 ? 0 : alpha;
            alpha = alpha > 1 ? 1 : alpha;
            if (power != 1.0)
                alpha = pow(alpha, power);

            return h1 * (1.0f - alpha) + h2 * alpha;
        }
        void updateCameraVectors();

    public:
        // camera Attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        glm::vec3 Center;
        // camera options
        float     MovementSpeed;
        float     MouseSensitivity;
        float     Zoom;
        glm::mat4 m_Projection;
    };

} // namespace DGERendering::Core
