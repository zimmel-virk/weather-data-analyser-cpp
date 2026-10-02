#ifndef FILTERS_H
#define FILTERS_H

#include <vector>
#include <string>
#include "Candlestick.h"

class Filters
{
public:
   
    // Filter by date range
    static std::vector<Candlestick> filterByDateRange(const std::vector<Candlestick> &candlesticks, const std::string &startDate, const std::string &endDate);

    // Filter by month across all years
    static std::vector<Candlestick> filterByMonthAcrossYears(const std::vector<Candlestick> &candlesticks, const std::string &targetMonth);

    // Filter by minimum temperature
    static std::vector<Candlestick> filterByMinTemperature(const std::vector<Candlestick> &candlesticks, double minTemp);

    // Filter by maximum temperature
    static std::vector<Candlestick> filterByMaxTemperature(const std::vector<Candlestick> &candlesticks, double maxTemp);

    // Filter by temperature range
    static std::vector<Candlestick> filterByTemperatureRange(const std::vector<Candlestick> &candlesticks, double minTemp, double maxTemp);

    // No filter (return all data)
    static std::vector<Candlestick> noFilter(const std::vector<Candlestick> &candlesticks);

    
};

#endif // FILTERS_H
