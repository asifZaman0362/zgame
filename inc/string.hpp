#pragma once
#include <string>
#include <vector>

namespace TstBits {
    // A container for std::string with some additional features
    class string {
    public:
        string();
        string(const char*);
        string(const std::string);
        string(const string&);
        string(const int);
        string(const double);
        ~string() = default;

        string operator+(const string&) const;
        string operator+(const std::string&) const;
        string operator+(const char*) const;
        string operator+(const int) const;
        string operator+(const double) const;
        string operator+(const char) const;

        string& operator+=(const string&);
        string& operator+=(const std::string&);
        string& operator+=(const char*);
        string& operator+=(const int);
        string& operator+=(const double);
        string& operator+=(const char);
        
        string operator*(const int);
        string& operator*=(const int);

        string& operator=(const string&);
        string& operator=(const std::string&);
        string& operator=(const char*);
        string& operator=(const int);
        string& operator=(const double);

        bool operator==(const string&) const;
        bool operator==(const std::string&) const;
        bool operator==(const char*) const;
        bool operator<(const string&) const;


        std::string str() const;

        int length() const;

        const char* c_str() const;

        std::vector<string> split(char, int=0) const;
        
        void clear();

        static string join(const std::vector<string>&, char='\0');

        static string format(const char*, ...);

        struct Compare { bool operator()(const string&, const string&) const; };

    
    private:
        std::string std_string;

    };
}