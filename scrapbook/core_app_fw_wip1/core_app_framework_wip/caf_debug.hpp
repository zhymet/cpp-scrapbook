#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <filesystem>

namespace caf {
    class logger {
    private:
        std::vector<std::string> logMessages;
    public:
        // Log function to add messages to the storage
        void log(const std::string& message) {
            namespace fs = std::filesystem;
            // Get current time
            auto currentTime = std::chrono::system_clock::now();

            // Format time as a string
            std::stringstream timeStringStream;
            timeStringStream << std::chrono::zoned_time{ std::chrono::current_zone(), currentTime };
            std::string timeStr = timeStringStream.str();

            // Get location in code using __FILE__ and __LINE__
            std::string location = std::string(__FILE__) + ":" + std::to_string(__LINE__);

            // Create the log entry
            std::string logEntry = timeStr + " [" + location + "] " + message;

            // Store the log entry
            logMessages.push_back(logEntry);
        }

        // Log function to add messages to the storage, and print to std::cout
        void log_print(const std::string& message) {
            namespace fs = std::filesystem;
            // Get current time
            auto currentTime = std::chrono::system_clock::now();

            // Format time as a string
            std::stringstream timeStringStream;
            timeStringStream << std::chrono::zoned_time{ std::chrono::current_zone(), currentTime };
            std::string timeStr = timeStringStream.str();

            // Get location in code using __FILE__ and __LINE__
            std::string location = std::string(__FILE__) + ":" + std::to_string(__LINE__);

            // Create the log entry
            std::string logEntry = timeStr + " [" + location + "] " + message;

            // Print the log entry to std::cout
            std::cout << logEntry << std::endl;

            // Store the log entry
            logMessages.push_back(logEntry);
        }

        // Store function to write messages to a file
        void store(const char* filename) const {
            namespace fs = std::filesystem;
            // Use std::filesystem to check if the file exists
            if (fs::exists(filename)) {
                // Remove the file if it exists
                fs::remove(filename);
            }

            // Open the file for writing
            std::ofstream file(filename, std::ios::out);

            if (file.is_open()) {
                // Write each log message to the file
                for (const auto& logEntry : logMessages) {
                    file << logEntry << "\n";
                }

                file.close();
            }
            else {
                std::cerr << "Unable to open " << filename << " for writing." << std::endl;
            }
        }
    };

    namespace debug {
        logger debug_logger{};
    };
};

/*
write a c++ class named logger that will print messages to std::cout.
It will store these messages as strings in the order they were called.
The class will receive messages through a method which may be called anywhere else named "log".
The function signature of log should look like:
void log(string message)

The stored messaged should contain this data:
- The string message
- The time this message was called
- The location in code from which this message was called

The class will be able to write the stored messages to a file called "debug_log.txt" . Making a newline for each message. The file will be overwritten every time the messaged are stored.
void store();

Do not use external libraries. Use std::filesystem for file operations. Use std::chrono library for time operations.
*/