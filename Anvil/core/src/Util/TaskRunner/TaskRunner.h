#pragma once
#include "../../Base/settings.hpp"
#include <string>

namespace Anvil
{

	class TaskRunner
	{

	public:
		typedef void (*CallbackFunction)(std::string);

		static std::string Execute(const char* cmd, const char* filename = "cmd_output.txt");

		/// <summary>
		/// Silently execute a command.
		/// </summary>
		/// <param name="cmd">command</param>
		/// <param name="callback">Callback function, hase to take in a string, calls if failed</param>
		/// <param name="filename">intermediate file</param>
		/// <returns>exit code, 0 if successful</returns>
		static int SilentExecute(const char* cmd, CallbackFunction callback = NULL, const char* filename = "cmd_output.txt");
	};

}