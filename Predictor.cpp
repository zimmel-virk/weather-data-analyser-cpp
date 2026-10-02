// Predictor.cpp
#include "Predictor.h"
#include <numeric>

// Function to predict future temperatures using a moving average method
// Parameters:
// - candlesticks: A vector of historical candlestick data
// - windowSize: The size of the moving average window (number of periods to consider for prediction)
// - futurePeriods: The number of future periods to predict
// - periodType: The type of period ('d' for daily, 'm' for monthly, 'y' for yearly)
std::vector<Candlestick> predictFutureTemperatures(const std::vector<Candlestick> &candlesticks, int windowSize, int futurePeriods, char periodType)
{
    std::vector<Candlestick> predictions;                        // Vector to store predicted candlestick data
    std::vector<Candlestick> workingCandlesticks = candlesticks; // Copy of the original data to work with

    // If there isn't enough data for the given window size, return an empty vector
    if (candlesticks.size() < windowSize)
    {
        return predictions;
    }

    // Determine the increment for calculating the next date based on the period type
    int increment = (periodType == 'd') ? 1 : (periodType == 'm') ? 30 : 365;

    // Get the last date from the historical dataset
    std::string lastDate = candlesticks.back().date;
    int lastYear = std::stoi(lastDate.substr(0, 4));
    int lastMonth = std::stoi(lastDate.substr(5, 2));
    int lastDay = std::stoi(lastDate.substr(8, 2));

    // Loop to predict the specified number of future periods
    for (int i = 0; i < futurePeriods; ++i)
    {
        double sumHigh = 0, sumLow = 0, sumOpen = 0, sumClose = 0;

        // Calculate the moving averages for the last `windowSize` periods
        for (size_t j = workingCandlesticks.size() - windowSize; j < workingCandlesticks.size(); ++j)
        {
            sumHigh += workingCandlesticks[j].high;
            sumLow += workingCandlesticks[j].low;
            sumOpen += workingCandlesticks[j].open;
            sumClose += workingCandlesticks[j].close;
        }

        // Compute the average values for the predicted candlestick
        double avgHigh = sumHigh / windowSize;
        double avgLow = sumLow / windowSize;
        double avgOpen = sumOpen / windowSize;
        double avgClose = sumClose / windowSize;

        // Calculate the next date for the prediction
        lastDay += increment;
        if (lastDay > 30)
        {
            lastDay = 1;
            ++lastMonth;
        }
        if (lastMonth > 12)
        {
            lastMonth = 1;
            ++lastYear;
        }

        // Format the predicted date as a string (YYYY-MM-DD)
        std::string predictedDate = std::to_string(lastYear) + "-" +
                                    (lastMonth < 10 ? "0" : "") + std::to_string(lastMonth) + "-" +
                                    (lastDay < 10 ? "0" : "") + std::to_string(lastDay);

        // Create a new candlestick object with the predicted values
        predictions.emplace_back(predictedDate, avgOpen, avgHigh, avgLow, avgClose);

        // Add the new prediction to the working dataset for subsequent predictions
        workingCandlesticks.push_back(predictions.back());
    }

    // Return the vector of predicted candlesticks
    return predictions;
}
