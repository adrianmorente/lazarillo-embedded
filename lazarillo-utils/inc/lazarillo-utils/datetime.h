#ifndef LAZARILLO_UTILS_INC_DATETIME_H
#define LAZARILLO_UTILS_INC_DATETIME_H

#include <chrono>
#include <string>

namespace utils
{
using Datetime =
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>;

/**
 * Returns the current time
 *
 * @return Datetime
 */
Datetime now();

/**
 * Returns the specified datetime as string in the format below:
 * "2022-08-19_16:41:23:001"
 *
 * @param p_datetime
 * @return std::string
 */
std::string to_string(Datetime const &p_datetime);

} // namespace utils

#endif // LAZARILLO_UTILS_INC_DATETIME_H
