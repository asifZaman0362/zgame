#pragma once
#include <vector>

namespace TstBits
{
    class string;
    class object;

    class Logger {
    public:
        Logger() = delete;
        ~Logger() = default;

        // Log a message
        static void LogMsg(const string&);
        //static void LogMsg(const char*);
        // Log a message along with a reference to the logging object
        static void LogMsg(const string&, const object&);
        //static void LogMsg(const char*, const object&);
        // Log an error message
        static void LogErr(const string&);
        //static void LogErr(const char*);
        // Log an error message with a reference to the logging object
        static void LogErr(const string&, const object&);
        //static void LogErr(const char*, const object&);
        // Write out all the logs to a file at the given path
        static void OutLog(const char*);

    private:
        static std::vector<string> messages;
    };
}