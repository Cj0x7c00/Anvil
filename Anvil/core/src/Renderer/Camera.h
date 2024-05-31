#pragma once
#include "../Base/macros.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Anvil
{
    enum ProjType
    {
        PROJ_TYPE_ORTHOGRAPHIC,
        PROJ_TYPE_PERSPECTIVE
    };

    class ANV_API Camera {
    public:
        Camera();

        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix();

        void SetPosition(const glm::vec3& newpos);
        void SetRotation(float yaw, float pitch);
        void Move(const glm::vec3& offset);
        void Rotate(float yawOffset, float pitchOffset);
        void SetPlains(float near, float far);
        void SetProjectionType(ProjType _ty);

        void updateCameraVectors();

        glm::vec3 position;
        // X: Pitch, Y: Yaw
        glm::vec3 rotation;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;


        float FOV;
        float Near;
        float Far;
        ProjType pType;
    };
}

