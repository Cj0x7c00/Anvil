#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <filesystem> // Include the filesystem library for file operations

namespace Anvil
{

    class Log {
    public:
        // Static log function to format and print log messages
        template <typename... Args>
        static void log(std::string func, const std::string& format, Args... args) {
            std::string message = formatString(format, args...);
            std::cout << "\033[1;30m[INFO : " << func << "()]: \033[0m" << message << std::endl;
        }

        template <typename... Args>
        static void debug(std::string func, const std::string& format, Args... args) {
            std::string message = formatString(format, args...);
            std::cout << "\033[1;32m[DBUG : " << func << "()]: \033[0m" << message << std::endl;
        }

        template <typename... Args>
        static void warn(std::string func, const std::string& format, Args... args) {
            std::string message = formatString(format, args...);
            std::cout << "\033[1;33m[WARN : " << func << "()]: \033[0m" << message << std::endl;
        }

        template <typename... Args>
        static void error(std::string func, const std::string& format, Args... args) {
            std::string message = formatString(format, args...);
            std::cout << "\033[1;31m[EROR : " << func << "()]: \033[0m" << message << std::endl;
            std::abort();
        }

    private:
        // Helper function to format the message
        template <typename... Args>
        static std::string formatString(const std::string& format, Args... args) {
            std::stringstream ss;
            formatStringInternal(ss, format, args...);
            return ss.str();
        }

        static std::string formatString(const std::string& format) {
            return format;
        }

        template <typename T>
        static void formatStringInternal(std::stringstream& ss, const std::string& format) {
            ss << format;
        }

        // Helper function to recursively format the message
        template <typename T>
        static void formatStringInternal(std::stringstream& ss, const std::string& format, T value) {
            size_t pos = format.find("{}");
            if (pos != std::string::npos) {
                ss << format.substr(0, pos) << value;
                formatStringInternal(ss, format.substr(pos + 2), value);
            }
            else {
                ss << format;
            }
        }


        template <typename T, typename... Args>
        static void formatStringInternal(std::stringstream& ss, const std::string& format, T value, Args... args) {
            size_t pos = format.find("{}");
            if (pos != std::string::npos) {
                ss << format.substr(0, pos) << value;
                formatStringInternal(ss, format.substr(pos + 2), args...);
            }
            else {
                ss << format;
            }
        }
    };

#define ENGINE_INFO(...)  Log::log  ( __FUNCTION__, __VA_ARGS__ )
#define ENGINE_DEBUG(...) Log::debug( __FUNCTION__, __VA_ARGS__ )
#define ENGINE_WARN(...)  Log::warn ( __FUNCTION__, __VA_ARGS__ )  
#define ENGINE_ERROR(...) Log::error( __FUNCTION__, __VA_ARGS__ )


#define ENGINE_ASSERT(condition_and_message) \
    do { \
        if (!(condition_and_message)) { \
            std::cerr << "Assertion failed: " << #condition_and_message << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl; \
            std::abort(); \
        } \
    } while (false);

#define ENGINE_OUT(message) logger::LOG(message, " ", 4)

}
