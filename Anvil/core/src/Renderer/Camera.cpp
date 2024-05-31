#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream> // For debugging
#include <Util/anvLog.hpp>

namespace Anvil {
    Camera::Camera()
        : position(glm::vec3(0.0f, 0.0f, 0.0f)),
        worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), // Ensure worldUp is correct
        rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
        FOV(100.f),
        Near(0.5f),
        Far(50.f),
        pType(PROJ_TYPE_PERSPECTIVE) {
        updateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix() {
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 Camera::GetProjectionMatrix() {
        float aspect = 1.0f; // Default aspect ratio, should be set by Renderer
        glm::mat4 projectionMatrix{ 0.0f };

        switch (pType) {
        case PROJ_TYPE_ORTHOGRAPHIC:
            /*TODO: Impl ortho projection*/
            std::cerr << "Camera projection set to orthographic which is NOT supported yet. Using perspective\n";
            projectionMatrix = glm::perspective(glm::radians(FOV), aspect, Near, Far);
            break;
        case PROJ_TYPE_PERSPECTIVE:
            projectionMatrix = glm::perspective(glm::radians(FOV), aspect, Near, Far);
            break;
        }

        return projectionMatrix;
    }

    void Camera::SetPosition(const glm::vec3& newpos) {
        position = newpos;
    }

    void Camera::SetRotation(float newYaw, float newPitch) {
        rotation.x = newPitch;
        rotation.y = newYaw;

        // Constrain the pitch
        if (rotation.x > 89.0f) rotation.x = 89.0f;
        if (rotation.y < -89.0f) rotation.y = -89.0f;

        updateCameraVectors();
    }

    void Camera::Move(const glm::vec3& offset) {
        position += offset;
    }

    void Camera::Rotate(float yawOffset, float pitchOffset) {
        rotation.x += pitchOffset;
        rotation.y += yawOffset;

        // Constrain the pitch
        if (rotation.x > 89.0f) rotation.x = 89.0f;
        if (rotation.x < -89.0f) rotation.x = -89.0f;

        updateCameraVectors();
    }

    void Camera::SetPlains(float near, float far) {
        Near = near;
        Far = far;
        ENGINE_DEBUG("Set near and far plains: N{}, F{}", Near, Far);
    }

    void Camera::SetProjectionType(ProjType _ty) {
        pType = _ty;
        ENGINE_DEBUG("Projection set to: {}", (pType == PROJ_TYPE_ORTHOGRAPHIC ? "Orthographic" : "Perspective"));
    }

    void Camera::updateCameraVectors() {
        // Calculate the new front vector
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
        newFront.y = sin(glm::radians(rotation.x));
        newFront.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
        front = glm::normalize(newFront);

        // Also re-calculate the Right and Up vector
        right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up = glm::normalize(glm::cross(right, front));

    }
}
