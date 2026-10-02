#include "CandlestickCalculator.h"
#include <algorithm>
#include <numeric>

// Function to calculate daily candlestick data from hourly temperature data.
// The function processes 24 hourly values at a time to compute a candlestick for each day.
std::vector<Candlestick> CandlestickCalculator::calculateDailyCandlesticks(const std::vector<double> &hourlyData)
{
    std::vector<Candlestick> dailyCandlesticks;
    double previousClose = 0.0;  // Initialize the previous day's closing value to 0.0

    // Iterate through the hourly data in 24-hour chunks
    for (size_t i = 0; i < hourlyData.size(); i += 24)
    {
        Candlestick candle;
        
        // The "Open" value is the previous day's average temperature
        candle.open = previousClose;
        
        // The "High" value is the maximum temperature of the day
        candle.high = *std::max_element(hourlyData.begin() + i, hourlyData.begin() + std::min(i + 24, hourlyData.size()));
        
        // The "Low" value is the minimum temperature of the day
        candle.low = *std::min_element(hourlyData.begin() + i, hourlyData.begin() + std::min(i + 24, hourlyData.size()));
        
        // The "Close" value is the average temperature of the day
        candle.close = std::accumulate(hourlyData.begin() + i, hourlyData.begin() + std::min(i + 24, hourlyData.size()), 0.0) / 24;

        // Add the candlestick to the daily candlesticks vector
        dailyCandlesticks.push_back(candle);
        
        // Update the previous close value for the next day's open
        previousClose = candle.close;
    }
    return dailyCandlesticks;
}

// Function to calculate monthly candlestick data from daily candlestick data.
// The function processes 30 daily candlesticks at a time to compute a candlestick for each month.
std::vector<Candlestick> CandlestickCalculator::calculateMonthlyCandlesticks(const std::vector<Candlestick> &dailyCandlesticks)
{
    std::vector<Candlestick> monthlyCandlesticks;
    double previousClose = 0.0;  // Initialize the previous month's closing value to 0.0

    // Iterate through the daily candlesticks in 30-day chunks
    for (size_t i = 0; i < dailyCandlesticks.size(); i += 30)
    {
        Candlestick candle;
        
        // The "Open" value is the previous month's average temperature
        candle.open = previousClose;
        
        // The "High" value is the highest temperature recorded in the month
        candle.high = std::max_element(dailyCandlesticks.begin() + i, dailyCandlesticks.begin() + std::min(i + 30, dailyCandlesticks.size()),
                                       [](const Candlestick &a, const Candlestick &b) { return a.high < b.high; })
                          ->high;
        
        // The "Low" value is the lowest temperature recorded in the month
        candle.low = std::min_element(dailyCandlesticks.begin() + i, dailyCandlesticks.begin() + std::min(i + 30, dailyCandlesticks.size()),
                                      [](const Candlestick &a, const Candlestick &b) { return a.low < b.low; })
                         ->low;
        
        // The "Close" value is the average temperature of the month
        candle.close = std::accumulate(dailyCandlesticks.begin() + i, dailyCandlesticks.begin() + std::min(i + 30, dailyCandlesticks.size()), 0.0,
                                      [](double sum, const Candlestick &c) { return sum + c.close; }) / 30;

        // Add the candlestick to the monthly candlesticks vector
        monthlyCandlesticks.push_back(candle);
        
        // Update the previous close value for the next month's open
        previousClose = candle.close;
    }
    return monthlyCandlesticks;
}

// Function to calculate yearly candlestick data from monthly candlestick data.
// The function processes 12 monthly candlesticks at a time to compute a candlestick for each year.
std::vector<Candlestick> CandlestickCalculator::calculateYearlyCandlesticks(const std::vector<Candlestick> &monthlyCandlesticks)
{
    std::vector<Candlestick> yearlyCandlesticks;
    double previousClose = 0.0;  // Initialize the previous year's closing value to 0.0

    // Iterate through the monthly candlesticks in 12-month chunks
    for (size_t i = 0; i < monthlyCandlesticks.size(); i += 12)
    {
        Candlestick candle;
        
        // The "Open" value is the previous year's average temperature
        candle.open = previousClose;
        
        // The "High" value is the highest temperature recorded in the year
        candle.high = std::max_element(monthlyCandlesticks.begin() + i, monthlyCandlesticks.begin() + std::min(i + 12, monthlyCandlesticks.size()),
                                       [](const Candlestick &a, const Candlestick &b) { return a.high < b.high; })
                          ->high;
        
        // The "Low" value is the lowest temperature recorded in the year
        candle.low = std::min_element(monthlyCandlesticks.begin() + i, monthlyCandlesticks.begin() + std::min(i + 12, monthlyCandlesticks.size()),
                                      [](const Candlestick &a, const Candlestick &b) { return a.low < b.low; })
                         ->low;
        
        // The "Close" value is the average temperature of the year
        candle.close = std::accumulate(monthlyCandlesticks.begin() + i, monthlyCandlesticks.begin() + std::min(i + 12, monthlyCandlesticks.size()), 0.0,
                                      [](double sum, const Candlestick &c) { return sum + c.close; }) / 12;

        // Add the candlestick to the yearly candlesticks vector
        yearlyCandlesticks.push_back(candle);
        
        // Update the previous close value for the next year's open
        previousClose = candle.close;
    }
    return yearlyCandlesticks;
}
