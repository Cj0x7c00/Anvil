#pragma once

/// <summary>
/// GLFW -> Anvil key mappings
/// </summary>

namespace Anvil
{
	enum InputKeys
	{
		ANV_KEY_SPACE = 32,
		
		/* Alpha */
		ANV_KEY_A = 65,
		ANV_KEY_B = 66,
		ANV_KEY_C = 67,
		ANV_KEY_D = 68,
		ANV_KEY_E = 69,
		ANV_KEY_F = 70,
		ANV_KEY_G = 71,
		ANV_KEY_H = 72,
		ANV_KEY_I = 73,
		ANV_KEY_J = 74,
		ANV_KEY_K = 75,
		ANV_KEY_L = 76,
		ANV_KEY_M = 77,
		ANV_KEY_N = 78,
		ANV_KEY_O = 79,
		ANV_KEY_P = 80,
		ANV_KEY_Q = 81,
		ANV_KEY_R = 82,
		ANV_KEY_S = 83,
		ANV_KEY_T = 84,
		ANV_KEY_U = 85,
		ANV_KEY_V = 86,
		ANV_KEY_W = 87,
		ANV_KEY_X = 88,
		ANV_KEY_Y = 89,
		ANV_KEY_Z = 90,

		/* Arows */
		ANV_KEY_RIGHT = 262,
		ANV_KEY_LEFT = 263,
		ANV_KEY_DOWN = 264,
		ANV_KEY_UP = 265

	};

	enum MouseMode
	{
		MOUSE_MODE_FREE = true,
		MOUSE_MODE_LOCKED = false
	};
}
