#pragma once
#include "../Base/macros.hpp"
#include <string>
#include <functional>

struct Vec2
{
	float x;
	float y;

	Vec2(float _x, float _y)
		: x(_x), y(_y)
	{

	}

	Vec2() {}
};

namespace Anvil
{
	class ANV_API CanvasItem
	{
	public:
		std::string item;

		CanvasItem(std::string _item)
			: item{_item}
		{

		}

		virtual void Draw() {};
	};

	class ANV_API UI_Button : public CanvasItem
	{
	public:
		static std::string item;

		const char* label;
		Vec2 size;
		Vec2 position;
		std::function<void()> Fn;

		UI_Button(const char* _label="New Button", Vec2 _size = Vec2(0, 0), Vec2 _pos = Vec2(0, 0), std::function<void()> _Fn = nullptr)
			: label{ _label }, size{ _size }, position{ _pos }, Fn{_Fn}, CanvasItem(item)
		{

		}

		void Draw() override;
	};


	class ANV_API UI_Rect : public CanvasItem
	{
	public:
		static std::string item;

		const char* name;
		Vec2 size;
		Vec2 position;
		std::function<void()> InnerElements; // inner elements

		UI_Rect(const char* _name = "New Rect", Vec2 _size = Vec2(300, 300), Vec2 _pos = Vec2(60, 60), std::function<void()> Elements = nullptr/*TODO: Window Flags*/)
			: name{ _name }, size{ _size }, position{ _pos }, InnerElements{Elements}, CanvasItem(item)
		{
			
		}

		void Draw() override;
	};

	class ANV_API UI_Text : public CanvasItem
	{
	public:
		static std::string item;

		const char* text;

		UI_Text(const char* Text)
			: text{ Text }, CanvasItem(item)
		{

		}

		virtual void Draw();
	};
}