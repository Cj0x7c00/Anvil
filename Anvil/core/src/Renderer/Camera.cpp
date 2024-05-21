#include "Camera.h"

#include "SwapChain.h"
#include "Renderer.h"

namespace Anvil
{

    Camera::Camera() : position(glm::vec3(0.0f, 0.0f, 0.0f)), worldUp(glm::vec3(0.0f, 0.0f, 1.0f)), yaw(0.0f), pitch(0.0f),
        FOV(100.f) {

        SetPlains(.01f, 200.f);
        updateCameraVectors();

    }

    glm::mat4 Camera::GetViewMatrix() const {
        return glm::lookAt(position, position * front, up);
    }

    glm::mat4 Camera::GetProjectionMatrix() const {
        return glm::perspective(glm::radians(FOV), Renderer::GetSwapChain()->GetAspectRatio(), Near, Far);
    }

    void Camera::SetPosition(const glm::vec3& newpos) {
        position = newpos;
    }

    void Camera::SetRotation(float yaw, float pitch) {
        this->yaw = yaw;
        this->pitch = pitch;
        updateCameraVectors();
    }

    void Camera::Move(const glm::vec3& offset) {
        position += offset;
    }

    void Camera::Rotate(float yawOffset, float pitchOffset) {
        yaw += yawOffset;
        pitch += pitchOffset;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        updateCameraVectors();
    }

    void Camera::SetPlains(float near, float far)
    {
        Near = near;
        Far = far;
        ENGINE_DEBUG("Set near and far plains: {}, {}", Near, Far);
    }

    void Camera::updateCameraVectors() {
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
}