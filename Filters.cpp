// Filters.cpp
#include "Filters.h"
#include <algorithm>

// Function to filter candlestick data by a specified date range
// Parameters:
// - candlesticks: A vector of candlesticks to be filtered
// - startDate: The start date of the desired range (inclusive)
// - endDate: The end date of the desired range (exclusive)
std::vector<Candlestick> Filters::filterByDateRange(const std::vector<Candlestick> &candlesticks, const std::string &startDate, const std::string &endDate)
{
    std::vector<Candlestick> filtered; // Vector to store filtered data

    // Iterate over each candlestick to check if its date falls within the specified range
    for (const auto &candle : candlesticks)
    {
        if (candle.date >= startDate && candle.date < endDate)
        {
            filtered.push_back(candle); // Add the candlestick to the filtered list if it matches the criteria
        }
    }
    return filtered; // Return the filtered vector
}

// Function to filter candlestick data by a specific month across all years
// Parameters:
// - candlesticks: A vector of candlesticks to be filtered
// - targetMonth: The month to filter by (in MM format)
std::vector<Candlestick> Filters::filterByMonthAcrossYears(const std::vector<Candlestick> &candlesticks, const std::string &targetMonth)
{
    std::vector<Candlestick> filtered; // Vector to store filtered data

    // Iterate over each candlestick to check if its date contains the target month
    for (const auto &candle : candlesticks)
    {
        if (candle.date.substr(5, 2) == targetMonth)
        {
            filtered.push_back(candle); // Add the candlestick to the filtered list if it matches the criteria
        }
    }
    return filtered; // Return the filtered vector
}

// Function to filter candlestick data by a minimum temperature value
// Parameters:
// - candlesticks: A vector of candlesticks to be filtered
// - minTemp: The minimum temperature to filter by
std::vector<Candlestick> Filters::filterByMinTemperature(const std::vector<Candlestick> &candlesticks, double minTemp)
{
    std::vector<Candlestick> filtered; // Vector to store filtered data

    // Iterate over each candlestick to check if its low value is greater than or equal to the minimum temperature
    for (const auto &candle : candlesticks)
    {
        if (candle.low >= minTemp)
        {
            filtered.push_back(candle); // Add the candlestick to the filtered list if it matches the criteria
        }
    }
    return filtered; // Return the filtered vector
}

// Function to filter candlestick data by a maximum temperature value
// Parameters:
// - candlesticks: A vector of candlesticks to be filtered
// - maxTemp: The maximum temperature to filter by
std::vector<Candlestick> Filters::filterByMaxTemperature(const std::vector<Candlestick> &candlesticks, double maxTemp)
{
    std::vector<Candlestick> filtered; // Vector to store filtered data

    // Iterate over each candlestick to check if its high value is less than or equal to the maximum temperature
    for (const auto &candle : candlesticks)
    {
        if (candle.high <= maxTemp)
        {
            filtered.push_back(candle); // Add the candlestick to the filtered list if it matches the criteria
        }
    }
    return filtered; // Return the filtered vector
}

// Function to filter candlestick data by a temperature range
// Parameters:
// - candlesticks: A vector of candlesticks to be filtered
// - minTemp: The minimum temperature of the range
// - maxTemp: The maximum temperature of the range
std::vector<Candlestick> Filters::filterByTemperatureRange(const std::vector<Candlestick> &candlesticks, double minTemp, double maxTemp)
{
    std::vector<Candlestick> filtered; // Vector to store filtered data

    // Iterate over each candlestick to check if its low and high values fall within the specified range
    for (const auto &candle : candlesticks)
    {
        if (candle.low >= minTemp && candle.high <= maxTemp)
        {
            filtered.push_back(candle); // Add the candlestick to the filtered list if it matches the criteria
        }
    }
    return filtered; // Return the filtered vector
}

// Function to return all candlestick data without applying any filters
// Parameters:
// - candlesticks: A vector of candlesticks to be returned as is
std::vector<Candlestick> Filters::noFilter(const std::vector<Candlestick> &candlesticks)
{
    return candlesticks; // Return the input vector without any modifications
}
