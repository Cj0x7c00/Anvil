#pragma once
#include "../Base/macros.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Anvil
{
    class ANV_API Camera {
    public:
        Camera();

        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;

        void SetPosition(const glm::vec3& newpos);
        void SetRotation(float yaw, float pitch);

        void Move(const glm::vec3& offset);
        void Rotate(float yawOffset, float pitchOffset);

        void SetPlains(float near = 1.f, float far = 20.f);

    private:
        void updateCameraVectors();

        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        float yaw;
        float pitch;

        float FOV;

        float Near, Far;
    };
}

