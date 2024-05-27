#include "Camera.h"
#include "SwapChain.h"
#include "Renderer.h"
#include "glm/gtx/string_cast.hpp"
#include <iostream>

namespace Anvil
{

    Camera::Camera() : position(glm::vec3(0.0f, 0.0f, 0.0f)), worldUp(glm::vec3(0.0f, 0.0f, 1.0f)), yaw(0.0f), pitch(0.0f),
        FOV(100.f) {

        SetProjectionType(PROJ_TYPE_PERSPECTIVE);
        SetPlains(.01f, 200.f);
        updateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix() {
        glm::mat4 viewMatrix = glm::lookAt(position, position + front, up);
        //std::cout << "View Matrix: " << glm::to_string(viewMatrix) << std::endl;
        return viewMatrix;
    }

    glm::mat4 Camera::GetProjectionMatrix() {
        glm::mat4 projectionMatrix{ 0.0f };

        float aspect = Renderer::GetSwapChain()->GetAspectRatio();
        //std::cout << "Aspect Ratio: " << aspect << std::endl;

        switch (pType) {
        case PROJ_TYPE_ORTHOGRAPHIC:
            /*TODO: Impl ortho projection*/
            ENGINE_WARN("Camera projection set to orthographic which is NOT supported yet. Using perspective");
            projectionMatrix = glm::perspective(glm::radians(FOV), aspect, Near, Far);
            break;
        case PROJ_TYPE_PERSPECTIVE:
            projectionMatrix = glm::perspective(glm::radians(FOV), aspect, Near, Far);
            break;
        }

        //std::cout << "Projection Matrix: " << glm::to_string(projectionMatrix) << std::endl;
        return projectionMatrix;
    }

    void Camera::SetPosition(const glm::vec3& newpos) {
        position = newpos;
        std::cout << "Camera Position: " << glm::to_string(position) << std::endl;
    }

    void Camera::SetRotation(float yaw, float pitch) {
        this->yaw = yaw;
        this->pitch = pitch;
        updateCameraVectors();
        std::cout << "Camera Rotation - Yaw: " << yaw << ", Pitch: " << pitch << std::endl;
    }

    void Camera::Move(const glm::vec3& offset) {
        position += offset;
        ENGINE_DEBUG("Camera Move - New Position: {}", glm::to_string(position));
    }

    void Camera::Rotate(float yawOffset, float pitchOffset) {
        yaw += yawOffset;
        pitch += pitchOffset;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        updateCameraVectors();
        ENGINE_DEBUG("Camera Rotate - Yaw: {}, Pitch: {}", yaw, pitch);
    }

    void Camera::SetPlains(float near, float far) {
        Near = near;
        Far = far;
        ENGINE_DEBUG("Set near and far plains: {}, {}", Near, Far);
    }

    void Camera::SetProjectionType(ProjType _ty) {
        pType = _ty;
        ENGINE_DEBUG("Projection set to: {}", (pType == PROJ_TYPE_ORTHOGRAPHIC) ? "Orthographic" : "Perspective");
    }

    void Camera::updateCameraVectors() {
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));/**/
        front = glm::normalize(front);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));

        ENGINE_DEBUG("Camera Vectors - Front: {} Right: {} Up: {}", glm::to_string(front), glm::to_string(right), glm::to_string(up));
    }
}
