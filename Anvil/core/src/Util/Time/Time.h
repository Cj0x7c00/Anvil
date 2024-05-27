#pragma once
#include <chrono>

#include "../../Base/macros.hpp"

namespace Anvil
{

	class ANV_API Profiler 
	{
	public:

		Profiler(const char* prof_name);
		~Profiler();

		const char* m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_sTime;

		friend class Time;
	};

	class ANV_API Time
	{
	public:
		static Profiler Profile(const char* name);

		static float DeltaTime();

	private:
		static void startEngineClock();
		static void update();

	private:
		static std::chrono::high_resolution_clock::time_point lastFrameTime;
		static std::chrono::high_resolution_clock::time_point currentFrameTime;

		friend class AnvilApplication;
	};


}

