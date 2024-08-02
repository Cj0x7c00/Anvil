#pragma once
#include "../Base/macros.hpp"
#include "Keys.h"

namespace Anvil
{

	class ANV_API Input
	{
	public:
		static bool IsKeyPressed(int keycode);
		static std::pair<float, float> GetMousePos();

		static void SetMouseMode(Anvil::MouseMode _m);

    protected:
		virtual bool Impl_IsKeyPressed(int keycode) = 0;
		virtual std::pair<float, float> Impl_GetMousePos() = 0;
		virtual void Impl_SetMouseMode(MouseMode _m) = 0;

	private:
		static Input* sInstance;
		static MouseMode mouseMode;
	};
}
