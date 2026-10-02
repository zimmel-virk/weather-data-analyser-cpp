#ifndef CANDLESTICKCALCULATOR_H
#define CANDLESTICKCALCULATOR_H

#include <vector>
#include "Candlestick.h"

// The CandlestickCalculator class provides methods to calculate candlestick data from temperature readings
class CandlestickCalculator
{
public:
    // Method to calculate daily candlestick data from hourly temperature readings
    static std::vector<Candlestick> calculateDailyCandlesticks(const std::vector<double> &hourlyData);

    // Method to calculate monthly candlestick data from daily candlesticks
    static std::vector<Candlestick> calculateMonthlyCandlesticks(const std::vector<Candlestick> &dailyCandlesticks);

    // Method to calculate yearly candlestick data from monthly candlesticks
    static std::vector<Candlestick> calculateYearlyCandlesticks(const std::vector<Candlestick> &monthlyCandlesticks);
};

#endif // CANDLESTICKCALCULATOR_H