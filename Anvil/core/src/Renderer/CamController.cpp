#include "CamController.h"
#include "Input/Input.h"
#include "Input/Keys.h"

namespace Anvil
{
        CamController::CamController(Camera& cam)
            : camera(cam), movementSpeed(2.5f), mouseSensitivity(0.1f) {}

        void CamController::ProcessKeyboard(float deltaTime) {
            float velocity = movementSpeed * deltaTime;
            if (Input::IsKeyPressed(ANV_KEY_W)) {
                camera.Move(camera.front * velocity);
            }
            if (Input::IsKeyPressed(ANV_KEY_S)) {
                camera.Move(-camera.front * velocity);
            }
            if (Input::IsKeyPressed(ANV_KEY_A)) {
                camera.Move(-camera.right * velocity);
            }
            if (Input::IsKeyPressed(ANV_KEY_D)) {
                camera.Move(camera.right * velocity);
            }
            if (Input::IsKeyPressed(ANV_KEY_E)) {
                camera.Move(camera.up * velocity);
            }
            if (Input::IsKeyPressed(ANV_KEY_Q)) {
                camera.Move(-camera.up * velocity);
            }
        }

        void CamController::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
            xOffset *= mouseSensitivity;
            yOffset *= mouseSensitivity;

            camera.Rotate(xOffset, yOffset);

            if (constrainPitch) {
                if (camera.pitch > 89.0f) camera.pitch = 89.0f;
                if (camera.pitch < -89.0f) camera.pitch = -89.0f;
            }
        }

        void CamController::SetMovementSpeed(float speed) {
            movementSpeed = speed;
        }

        void CamController::SetMouseSensitivity(float sensitivity) {
            mouseSensitivity = sensitivity;
        }

}