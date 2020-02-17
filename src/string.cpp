#include "string.hpp"
#include "logger.hpp"
#include <string.h>
#include <cstdarg>


using ze::string;

string::string() : std_string("") {}
string::string(const char* str) : std_string(str) {}
string::string(std::string str) : std_string(str) {}
string::string(const string& str) : std_string(str.std_string) {}
string::string(const int i) : std_string(std::to_string(i)) {}
string::string(const double d) : std_string(std::to_string(d)) {}


/********* ADDITION OPERATOR ********/
/**** string + string/int/double ****/

string string::operator+(const string& right) const {
    string str_to_return;
    str_to_return.std_string = this->std_string + right.std_string;
    return str_to_return;
}

string string::operator+(const std::string& right) const {
    string str_to_return;
    str_to_return.std_string = this->std_string + right;
    return str_to_return;
}

string string::operator+(const char* right) const {
    string str_to_return;
    str_to_return.std_string = this->std_string + std::string(right);
    return str_to_return;
}

string string::operator+(const int right) const {
    string str_to_return;
    str_to_return.std_string = this->std_string + std::to_string(right);
    return str_to_return;
}

string string::operator+(const double right) const {
    string str_to_return;
    str_to_return.std_string = this->std_string + std::to_string(right);
    return str_to_return;
}

string string::operator+(const char right) const {
    string str_to_return;
    str_to_return.std_string = this->std_string + right;
    return str_to_return;
}

string& string::operator+=(const string& right) {
    this->std_string = this->std_string + right.std_string;
    return *this;
}

string& string::operator+=(const std::string& right) {
    this->std_string = this->std_string + right;
    return *this;
}

string& string::operator+=(const char* right) {
    this->std_string = this->std_string + std::string(right);
    return *this;
}

string& string::operator+=(const int right) {
    this->std_string = this->std_string + std::to_string(right);
    return *this;
}

string& string::operator+=(const double right) {
    this->std_string = this->std_string + std::to_string(right);
    return *this;
}

string& string::operator+=(const char right) {
    this->std_string = this->std_string + right;
    return *this;
}


/****** MULTIPLICATION OPERATOR *****/
/*********** string * int ***********/

string string::operator*(const int times) {
    string str_to_return;
    for (int i = 0; i < times; i++) {
        str_to_return += *this;
    }
    return str_to_return;
}

string& string::operator*=(const int times) {
    string str_temp;
    for (int i = 0; i < times; i++) {
        str_temp += *this;
    }
    this->std_string = str_temp.std_string;
    return *this;
}


/******** ASSIGNMENT OPERATOR *******/
/**** string = int/double/string ****/

string& string::operator=(const string& other) {
    if (&other == this) return *this;
    this->std_string = other.std_string;
    return *this;
}

string& string::operator=(const std::string& other) {
    this->std_string = other;
    return *this;
}

string& string::operator=(const char* other) {
    this->std_string = std::string(other);
    return *this;
}

string& string::operator=(const int i) {
    this->std_string = std::to_string(i);
    return *this;
}

string& string::operator=(const double d) {
    this->std_string = std::to_string(d);
    return *this;
}

/********* EQUALITY OPERATOR **********/
/**** string ==/< all string types ****/

bool string::operator==(const string& right) const {
    return this->std_string == right.std_string;
}

bool string::operator==(const std::string& right) const {
    return this->std_string == right;
}

bool string::operator==(const char* right) const {
    return this->std_string == right;
}

bool string::operator<(const string& right) const {
    return this->str() < right.str();
}


/************* FUNCTIONS *************/

std::string string::str() const {
    return std_string;
}

int string::length() const {
    return std_string.length();
}

const char* string::c_str() const {
    return std_string.c_str();
}

std::vector<string> string::split(char delimiter, int limit) const {

    std::vector<string> return_vector;
    const int len = length();
    const char* arr = c_str();
    std::string builder;
    for (int i = 0; i < len; i++) {
        if (arr[i] == delimiter && builder.length() > 0) {
            return_vector.push_back(string(builder));
            builder.clear();
        } else builder += arr[i];
    }
    if (builder.length() > 0) return_vector.push_back(string(builder));
    return return_vector;

}

void string::clear() {
    std_string.clear();
}

string string::join(const std::vector<string>& list, char joiner) {
    string return_string;
    const int len = list.size();
    for(int i = 0; i < len; i++) {
        return_string += list[i];
        if (joiner != '\0' && i != len - 1) return_string += joiner;
    }
    return return_string;
}

string string::format(const char* format, ...) {
    string return_string;
    const int len = strlen(format);
    va_list args;
    va_start(args, format);
    for (int i = 0; i < len; i++) {
        if (format[i] == '{' && format[i+2] == '}') {
            switch(format[i+1]) {
                case 'd':
                    return_string += va_arg(args, double);
                    i += 2;
                    break;
                case 'i':
                    return_string += va_arg(args, int);
                    i += 2;
                    break;
                case 's':
                    return_string += va_arg(args, const char*);
                    i += 2;
                    break;
                default:
                    Logger::LogErr("Wrong formatting or maybe not.");
            }
        } else return_string += format[i];
    }
    return return_string;
}

bool string::Compare::operator()(const string& a, const string& b) const {
    return a < b;
}
