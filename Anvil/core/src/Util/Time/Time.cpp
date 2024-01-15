#include "Time.h"
#include "../anvLog.hpp"

namespace Anvil
{
	Profiler::Profiler(const char* prof_name)
		: m_Name{prof_name}
	{
		m_sTime = std::chrono::high_resolution_clock::now();
	}

	Profiler::~Profiler()
	{
		auto end_point = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_sTime).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_point).time_since_epoch().count();

		auto duration = end - start;

		double ms = duration * 0.001;

		ENGINE_INFO("\033[35mProfile: {}: {}ms ({}mics)\033[0m", m_Name, ms, duration);

	}

	Profiler Time::Profile(const char* name)
	{
		return Profiler(name);
	}

}