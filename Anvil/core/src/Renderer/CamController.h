#pragma once
#include "Camera.h"
#include "../Base/macros.hpp"

namespace Anvil
{
	class ANV_API CamController
	{
    public:
        CamController(Camera& camera);

        void ProcessKeyboard(float deltaTime);
        void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

        void SetMovementSpeed(float speed);
        void SetMouseSensitivity(float sensitivity);

    private:
        Camera& camera;
        float movementSpeed;
        float mouseSensitivity;
	};
}

