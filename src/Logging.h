
#include <cstdarg>
#include <string>

const int LOGGING_MAX_STRLEN = 1024;

std::string printfString(const char *fmt, ...)
{
    va_list args;
    char msg[LOGGING_MAX_STRLEN];
    va_start(args, fmt);
    vsnprintf(msg, LOGGING_MAX_STRLEN, fmt, args);
    va_end(args);
    return msg;
}

