#include "CamController.h"
#include "Input/Input.h"

namespace Anvil {
    CameraController::CameraController(Camera& cam)
        : camera(cam), movementSpeed(2.5f), rotationSpeed(90.0f) {} // rotationSpeed is in degrees per second

    void CameraController::ProcessKeyboard(float deltaTime) {
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


        float rotation = rotationSpeed * deltaTime;
        float yawOffset = 0.0f;
        float pitchOffset = 0.0f;

        if (Input::IsKeyPressed(ANV_KEY_LEFT)) {
            yawOffset -= rotation;
        }
        if (Input::IsKeyPressed(ANV_KEY_RIGHT)) {
            yawOffset += rotation;
        }
        if (Input::IsKeyPressed(ANV_KEY_UP)) {
            pitchOffset += rotation;
        }
        if (Input::IsKeyPressed(ANV_KEY_DOWN)) {
            pitchOffset -= rotation;
        }

        camera.Rotate(yawOffset, pitchOffset);
    }

    void CameraController::SetMovementSpeed(float speed) {
        movementSpeed = speed;
    }

    void CameraController::SetRotationSpeed(float speed) {
        rotationSpeed = speed;
    }
}
