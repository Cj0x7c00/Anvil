#include "Input.h"

bool Anvil::Input::IsKeyPressed(int keycode)
{
	return sInstance->Impl_IsKeyPressed(keycode);
}
