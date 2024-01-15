#include "Time.h"

namespace Anvil
{
	Profiler::Profiler(const char* prof_name)
		: m_Name{prof_name}
	{

	}

	void Time::Profile(const char* name)
	{
		new Profiler(name);
	}
	Profiler::~Profiler()
	{
	}
}