#pragma once

#include <chrono>

namespace Anvil
{

	class Profiler 
	{
	private:

		Profiler(const char* prof_name);
		~Profiler();

		const char* m_Name;
		const std::chrono::steady_clock m_Time;

		friend class Time;
	};

	class Time
	{
	public:
		static void Profile(const char* name);

	};

}

