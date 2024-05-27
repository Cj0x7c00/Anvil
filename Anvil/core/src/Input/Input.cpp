#include "Input.h"

bool Anvil::Input::IsKeyPressed(int keycode)
{
	return sInstance->Impl_IsKeyPressed(keycode);
}

std::pair<float, float> Anvil::Input::GetMousePos()
{
	return sInstance->Impl_GetMousePos();
}

void Anvil::Input::SetMouseMode(Anvil::MouseMode _m)
{
	sInstance->Impl_SetMouseMode(_m);
}
