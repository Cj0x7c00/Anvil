#pragma once

#include <chrono>

namespace Anvil
{

	class Profiler 
	{
	public:

		Profiler(const char* prof_name);
		~Profiler();

		const char* m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_sTime;

		friend class Time;
	};

	class Time
	{
	public:
		static Profiler Profile(const char* name);

	};

}

