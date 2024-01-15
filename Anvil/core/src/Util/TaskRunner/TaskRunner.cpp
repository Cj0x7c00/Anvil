#include "TaskRunner.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdio>
#include "../anvLog.hpp"


namespace Anvil
{
    std::string TaskRunner::Execute(const char* cmd, const char* filename)
    {
        std::string result;

        // Execute the command and redirect its output to a file
        std::string commandWithRedirect = std::string(cmd) + " > " + filename;
        int exitCode = system(commandWithRedirect.c_str());

        std::ifstream outputFile{ filename };

        if (exitCode != 0) {
            ENGINE_WARN("Command execution failed: {}", exitCode);
        }

        if (!outputFile) {
            ENGINE_WARN("Failed to open the output file: {}", filename);
            return result; // Return an empty result if file couldn't be opened
        }

        std::string line;
        while (std::getline(outputFile, line)) {
            result += line + '\n';
        }

        outputFile.close(); // Close the file explicitly

        // Clean up: remove the output file
        if (remove(filename) != 0) {
            ENGINE_WARN("Failed to remove the output file.");
        }

        return result;
    }

    int TaskRunner::SilentExecute(const char* cmd, const char* filename)
    {

        // Execute the command and redirect its output to a file
        std::string commandWithRedirect = std::string(cmd) + " > " + filename;
        int exitCode = system(commandWithRedirect.c_str());

        if (exitCode != 0)
        {
            std::ifstream file(filename);
            std::string contents;

            std::string line;
            while (std::getline(file, line))
            {
                contents += line;
            }

            file.close();
        }

        if (remove(filename) != 0) {
            ENGINE_WARN("Failed to remove the output file.");
        }

        return exitCode;
    }
}