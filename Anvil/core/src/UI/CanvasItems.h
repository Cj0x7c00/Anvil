#pragma once
#include "../Base/macros.hpp"
#include "../Base/Pointer.hpp"
#include "../Util/anvLog.hpp"
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

	bool operator!=(const Vec2& other)
	{
		if (other.x == x && other.y == y)
		{
			return true;
		}

		return false;
	}
};

struct Vec4
{
	float x;
	float y;
	float z;
	float a;

	Vec4(float _x, float _y, float _z, float _a)
		: x(_x), y(_y), z(_z), a(_a)
	{

	}

	Vec4() {}
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


	class ANV_API UI_Window : public CanvasItem
	{
	public:
		static std::string item;

		const char* name;
		Vec2 size;
		Vec2 position;
		std::vector<Ref<CanvasItem>> InnerElements; // inner elements

		UI_Window(const char* _name = "New Window", Vec2 _size = Vec2(300, 300), Vec2 _pos = Vec2(60, 60))
			: name{ _name }, size{ _size }, position{ _pos }, CanvasItem(item)
		{
			
		}

		void Draw() override;

		template<typename Elm , typename... Args>
		void DrawElement(Args&&... args)
		{
			auto el = CreateRef<Elm>(std::forward<Args>(args)...);
			InnerElements.push_back(el);
		}
	};

	class ANV_API UI_Selectable : public CanvasItem
	{
	public:
		static std::string item;
		std::string text = "##";
		bool selected = false;
		Vec4 OnSelectedSetColor = Vec4(133.0, 158.0, 209.0, 0.8);

		UI_Selectable(std::string Text);

		void Draw() override;
	};

	class ANV_API UI_Menue : public CanvasItem
	{
	public:
		static std::string item;
		std::vector<std::string> menueItems;

		UI_Menue(std::vector<std::string> _mItems) :  menueItems{_mItems}, CanvasItem(item)
		{

		}

		void Draw() override;
	};
}