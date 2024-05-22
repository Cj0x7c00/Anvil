#pragma once
#include "../Base/macros.hpp"

namespace Anvil
{
	class ANV_API Input
	{
	public:
		static bool IsKeyPressed(int keycode);

    protected:
		virtual bool Impl_IsKeyPressed(int keycode) = 0;

	private:
		static Input* sInstance;
	};
}
