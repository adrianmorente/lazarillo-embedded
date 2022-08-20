#include "lazarillo-utils/datetime.h"

#include <iomanip>
#include <sstream>

namespace utils
{
Datetime now()
{
    return std::chrono::time_point_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now());
}

std::string to_string(Datetime const &p_datetime)
{
    auto const milliseconds{
        std::chrono::duration_cast<std::chrono::milliseconds>(
            p_datetime.time_since_epoch()) %
        1000};
    auto const timer = Datetime::clock::to_time_t(p_datetime);

    // Read time difference
    struct tm time;
    gmtime_r(&timer, &time);

    // %Y-%m-%d_%T equivalent to YEAR-MONTH-DAY_HOURS:MINUTES:SECONDS
    std::ostringstream oss;
    oss << std::put_time(&time, "%Y-%m-%d_%T");

    // Append milliseconds (3 digits)
    oss << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();
    return oss.str();
}

} // namespace utils
