#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    const int secsPerMinute = 60;
    const int minutesperHour = 60;
    auto totalMinutes = seconds / secsPerMinute;
    auto numHours = std::to_string(totalMinutes / minutesperHour);
    auto numMinutes = std::to_string(totalMinutes % minutesperHour);
    auto numSeconds = std::to_string(seconds % secsPerMinute);
    if (stoi(numHours) < 10)
        numHours = "0" + numHours;
    if (stoi(numMinutes) < 10)
        numMinutes = "0" + numMinutes;
    if (stoi(numSeconds) < 10)
        numSeconds = "0" + numSeconds;
    return numHours + ":" + numMinutes + ":" + numSeconds;




}