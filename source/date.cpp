#include <cstdio>
#include <ctime>
#include <string>
#include "date.h"

std::string get_datetime()
{
    try
    {
        time_t now = time(NULL);
        tm* ltm = localtime(&now);

        char buffer[20];

        sprintf(buffer, "%04u-%02u-%02u %02u:%02u:%02u",
            1900 + ltm->tm_year, 1 + ltm->tm_mon,
            ltm->tm_mday, ltm->tm_hour,
            ltm->tm_min, ltm->tm_sec);

        std::string date(buffer);

        return date;
    }
    catch (std::exception e) { throw; }
}
