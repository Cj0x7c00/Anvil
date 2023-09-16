#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <filesystem> // Include the filesystem library for file operations

// Define the RELEASE macro
#define DEBUG

class logger {
public:
    static void InitLogFile(const std::string& fileName) {
        // Create the directory if it doesn't exist
        //std::filesystem::create_directories(std::filesystem::path(fileName).parent_path());
        static std::ofstream logFile;
        logFile.open(fileName, std::ios::out | std::ios::app);
    }

    static void Cleanup() {
        static std::ofstream logFile;
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    static void LOG(std::string log_msg, std::string log_location, int log_code) {
        static std::ofstream logFile;
        static std::mutex mtx; // Mutex for thread safety

        if (log_code == 0) { // 0 is code for info
            std::ostringstream oss;
            oss << "[INFO] [" << "Location: " << log_location << "]: " << log_msg << '\n';

            std::string logString = oss.str();

            // Use a mutex for thread safety
            std::lock_guard<std::mutex> lock(mtx);

            if (logFile.is_open()) {
                logFile << logString;
                logFile.flush(); // Ensure the log is written immediately
            }
            else {
                std::cout << "\033[1;30m[INFO] \033[0m" << "\033[1;30m[" << "Location: " << log_location << "]: \033[0m"<< log_msg << '\n'; // Print to console in debug mode
            }
        }

        if (log_code == 1) { 
            std::ostringstream oss;
            oss << "[DBUG] [" << "Location: " << log_location << "]: " << log_msg << '\n';

            std::string logString = oss.str();

            // Use a mutex for thread safety
            std::lock_guard<std::mutex> lock(mtx);

            if (logFile.is_open()) {
                logFile << logString;
                logFile.flush(); // Ensure the log is written immediately
            }
            else {
                std::cout << "\033[1;32m[DBUG] \033[0m" << "\033[1;30m[" << "Location: " << log_location << "]: \033[0m" << log_msg << '\n'; // Print to console in debug mode
            }
        }

        if (log_code == 2) { 
            std::ostringstream oss;
            oss << "[WARN] [" << "Location: " << log_location << "]: " << log_msg << '\n';

            std::string logString = oss.str();

            // Use a mutex for thread safety
            std::lock_guard<std::mutex> lock(mtx);

            if (logFile.is_open()) {
                logFile << logString;
                logFile.flush(); // Ensure the log is written immediately
            }
            else {
                std::cout << "\033[1;33m[WARNING] \033[0m" << "\033[1;30m[" << "Location: " << log_location << "]: \033[0m" << log_msg << '\n'; // Print to console in debug mode
            }
        }

        if (log_code == 3) { 
            std::ostringstream oss;
            oss << "[ERROR] [" << "Location: " << log_location << "]: " << log_msg << '\n';

            std::string logString = oss.str();

            // Use a mutex for thread safety
            std::lock_guard<std::mutex> lock(mtx);

            if (logFile.is_open()) {
                logFile << logString;
                logFile.flush(); // Ensure the log is written immediately
            }
            std::cerr <<"\033[1;31m[ERROR] \033[0m" << "\033[1;30m[" << "Location: " << log_location << "]: \033[0m" << log_msg << "\n";

        }

        // Handle other log_code cases similarly
    }
};


#if defined(DEBUG)
#define ENGINE_INFO(message)  logger::LOG(message, std::string(__FILE__) + " | func : " + std::string(__FUNCTION__) + "() | line : " + std::to_string(__LINE__), 0)
#define ENGINE_DEBUG(message) logger::LOG(message, std::string(__FILE__) + " | func : " + std::string(__FUNCTION__) + "() | line : " + std::to_string(__LINE__), 1)
#define ENGINE_WARN(message)  logger::LOG(message, std::string(__FILE__) + " | func : " + std::string(__FUNCTION__) + "() | line : " + std::to_string(__LINE__), 2)
#define ENGINE_ERROR(message) logger::LOG(message, std::string(__FILE__) + " | func : " + std::string(__FUNCTION__) + "() | line : " + std::to_string(__LINE__), 3)

#define ENGINE_ASSERT(condition_and_message) \
    do { \
        if (!(condition_and_message)) { \
            std::cerr << "Assertion failed: " << #condition_and_message << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl; \
            std::abort(); \
        } \
    } while (false)

//#define ENGINE_INIT_LOG_FILE(fileName) (void(0))
//#define ENGINE_CLEANUP_LOG() (void(0))
// ...

#elif defined(RELEASE)
// Initialize the log file in release mode
#define ENGINE_INIT_LOG_FILE(fileName) logger::InitLogFile(fileName)
#define ENGINE_INFO(message)  logger::LOG(message, std::string(__FILE__) + " | func : " + std::string(__FUNCTION__) + "() | line : " + std::to_string(__LINE__), 0)
#define ENGINE_DEBUG(message) logger::LOG(message, std::string(__FILE__) + " | func : " + std::string(__FUNCTION__) + "() | line : " + std::to_string(__LINE__), 1)
#define ENGINE_WARN(message)  logger::LOG(message, std::string(__FILE__) + " | func : " + std::string(__FUNCTION__) + "() | line : " + std::to_string(__LINE__), 2)
ENGINE_ASSERT(condition_and_message) (void(0))
#define ENGINE_ERROR(message) logger::LOG(message, std::string(__FILE__) + " | func : " + std::string(__FUNCTION__) + "() | line : " + std::to_string(__LINE__), 3)
#define ENGINE_CLEANUP_LOG() logger::Cleanup()
// ...

#endif