#pragma once
#include "Camera.h"
#include "../Base/macros.hpp"

namespace Anvil
{
	class ANV_API CameraController
	{
    public:
        CameraController(Camera& camera);

        void ProcessKeyboard(float deltaTime);


        void SetMovementSpeed(float speed);
        void SetRotationSpeed(float sensitivity);

    private:
        Camera& camera;
        float movementSpeed;
        float rotationSpeed;
	};
}

