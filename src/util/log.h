#pragma once

#include <cstdarg>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "types.h"

class log
{
public:
    static void info(const char* fmt, ...)
    {
        va_list arg;
        va_start(arg, fmt);
        vfprintf(stdout, reformat(fmt, " INFO  ").c_str(), arg);
        va_end(arg);
    }
    
    static void info(const string& fmt, ...)
    {
        va_list arg;
        info(fmt.c_str(), arg);
    }
    
    static void warn(const char* fmt...)
    {
        va_list arg;
        va_start(arg, fmt);
        vfprintf(stdout, reformat(fmt, " WARN  ").c_str(), arg);
        va_end(arg);
    }
    
    static void warn(const string& fmt, ...)
    {
        va_list arg;
        info(fmt.c_str(), arg);
    }
    
    static void error(const char* fmt...)
    {
        va_list arg;
        va_start(arg, fmt);
        vfprintf(stderr, reformat(fmt, " ERROR ").c_str(), arg);
        va_end(arg);
    }
    
    static void error(const string& fmt, ...)
    {
        va_list arg;
        error(fmt.c_str(), arg);
    }
    
    static void fatal(const char* fmt...)
    {
        va_list arg;
        va_start(arg, fmt);
        vfprintf(stderr, reformat(fmt, " FATAL ").c_str(), arg);
        va_end(arg);
        exit(-1);
    }
    
    static void fatal(const string& fmt, ...)
    {
        va_list arg;
        fatal(fmt.c_str(), arg);
    }
    
    template<typename T> static void data(const vector<T>& d)
    {
        string data = " DATA  " + hex_str(d);
        cout << header() << data << "\n";
    }

private:
    static string reformat(const char* fmt, const char* level)
    {
        stringstream ss;
        ss << header() << level << fmt << "\n";
        return ss.str();
    }
    
    static string header()
    {
        time_t now = time(0);
        tm* local = localtime(&now);
        const int YEAR = 1900 + local->tm_year;
        const int MONTH = 1 + local->tm_mon;
        const int DAY = local->tm_mday;
        const int HOUR = local->tm_hour;
        const int MIN = local->tm_min;
        const int SEC = local->tm_sec;
        stringstream ss;
        ss << "[" 
        << setw(4) << setfill('0') << YEAR  << "-" 
        << setw(2) << setfill('0') << MONTH << "-" 
        << setw(2) << setfill('0') << DAY << " " 
        << setw(2) << setfill('0') << HOUR << ":" 
        << setw(2) << setfill('0') << MIN << ":" 
        << setw(2) << setfill('0') << SEC << "] ";
        return ss.str();
    }
    
    static string where(const char* file, size_t line)
    {
        return string(file) + ":" + to_string(line);
    }
    
    template<typename T> static string hex_str(const vector<T>& data)
    {
        size_t width = sizeof(T);
        stringstream  ss;
        for (T byte : data)
            ss << hex << setw(width * 2) << setfill('0') << (int) byte;
        return ss.str();
    }
};
