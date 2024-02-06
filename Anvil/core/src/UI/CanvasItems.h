#pragma once

#include <functional>

struct Vec2
{
	float x;
	float y;

	Vec2(float _x, float _y)
		: x(_x), y(_y)
	{

	}
};

namespace Anvil
{
	struct CanvasItem
	{
		virtual void Draw() = 0;
	};

	struct Button : CanvasItem
	{
		const char* label;
		Vec2 size;
		Vec2 position;
		std::function<void()> Fn;

		Button(const char* _label, Vec2 _size = Vec2(0, 0), Vec2 _pos = Vec2(0, 0), std::function<void()> _Fn=nullptr)
			: label{ _label }, size{ _size }, position{ _pos }, Fn{_Fn}
		{

		}

		void Draw() override;
	};
}