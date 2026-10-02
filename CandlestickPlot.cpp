// CandlestickPlot.cpp
#include "CandlestickPlot.h"
#include <iostream>
#include <iomanip>

// Function to plot the weather candlesticks as a text-based chart
// Parameters:
// - candlesticks: A vector containing candlestick objects to be plotted
// - chartHeight: The height of the text chart in lines
// - frequency: The time period frequency ('d' for daily, 'm' for monthly, 'y' for yearly)
void CandlestickPlot::plot(const std::vector<Candlestick> &candlesticks, int chartHeight, char frequency)
{
    // Check if the input candlestick data is empty
    if (candlesticks.empty())
    {
        std::cerr << "No data to plot." << std::endl;
        return;
    }

    // Initialize variables to track the minimum and maximum temperature values for the Y-axis
    double minTemp = candlesticks.front().low;
    double maxTemp = candlesticks.front().high;

    // Loop through all candlesticks to find the overall minimum and maximum temperatures
    for (const auto &candle : candlesticks)
    {
        if (candle.low < minTemp)
            minTemp = candle.low;
        if (candle.high > maxTemp)
            maxTemp = candle.high;
    }

    // Calculate the range of temperatures and the step size for each row in the chart
    double range = maxTemp - minTemp;
    double step = range / chartHeight;

    // Print the header of the chart
    std::cout << "\n======================= Weather Candlestick Chart =======================\n";

    // Loop to generate the plot row by row
    for (int i = chartHeight; i >= 0; --i)
    {
        // Calculate the current temperature for this row
        double currentTemp = minTemp + i * step;

        // Print the Y-axis label with temperature in °C
        std::cout << std::setw(6) << std::fixed << std::setprecision(1) << currentTemp << "°C | ";

        // Loop through each candlestick to plot the corresponding symbols for high, low, open, and close values
        for (size_t j = 0; j < candlesticks.size(); ++j)
        {
            const auto &candle = candlesticks[j];

            // Add spacing between candlesticks for better readability
            std::cout << std::setw(5);

            // Determine which symbol to plot based on the current temperature and candlestick values
            if (std::abs(currentTemp - candle.high) < step / 2.0)
            {
                std::cout << " | "; // High stalk
            }
            else if (std::abs(currentTemp - candle.low) < step / 2.0)
            {
                std::cout << " | "; // Low stalk
            }
            else if (std::abs(currentTemp - candle.open) < step / 2.0)
            {
                std::cout << "----"; // Open value
            }
            else if (std::abs(currentTemp - candle.close) < step / 2.0)
            {
                std::cout << "----"; // Close value
            }
            else if (currentTemp < candle.high && currentTemp > candle.low)
            {
                std::cout << " | "; // Inside stalk
            }
            else
            {
                std::cout << "     "; // Empty space
            }
        }

        // Move to the next row
        std::cout << std::endl;
    }

    // Print the X-axis labels based on the selected frequency (daily, monthly, yearly)
    if (frequency == 'd')
    {
        printDailyXAxis(candlesticks);
    }
    else if (frequency == 'm')
    {
        printMonthlyXAxis(candlesticks);
    }
    else if (frequency == 'y')
    {
        printYearlyXAxis(candlesticks);
    }

    // Note about the representation of open/close values
    std::cout << "\nNote:\n";
    std::cout << "If Open and Close values are closer than " << step / 2.0
              << "°C (based on the current Y-axis resolution), they are represented by a single horizontal line ('----').\n";
}

// Helper function to print daily X-axis labels
void CandlestickPlot::printDailyXAxis(const std::vector<Candlestick> &candlesticks)
{
    // Extract the start day from the first candlestick's date
    int startDay = std::stoi(candlesticks.front().date.substr(8, 2));

    // Print day numbers with proper spacing
    std::cout << "       ";
    for (size_t i = 0; i < candlesticks.size(); ++i)
    {
        std::cout << std::setw(5) << (startDay + i);
    }
    std::cout << "\n       ";

    // Print the month number as a label in the middle of the X-axis
    if (!candlesticks.empty())
    {
        std::cout << std::setw(5 * candlesticks.size() / 2) << candlesticks.front().date.substr(5, 2) << "\n";
    }
}

// Helper function to print monthly X-axis labels
void CandlestickPlot::printMonthlyXAxis(const std::vector<Candlestick> &candlesticks)
{
    // Extract the start month from the first candlestick's date
    int startMonth = std::stoi(candlesticks.front().date.substr(5, 2));

    // Print month numbers with proper spacing
    std::cout << "       ";
    for (size_t i = 0; i < candlesticks.size(); ++i)
    {
        std::cout << std::setw(5) << ((startMonth + i - 1) % 12 + 1);
    }
    std::cout << "\n       ";

    // Print the year labels at the appropriate positions
    for (size_t i = 0; i < candlesticks.size(); ++i)
    {
        if ((startMonth + i - 1) % 12 == 0)
        {
            std::cout << std::setw(5) << candlesticks[i].date.substr(0, 4);
        }
        else
        {
            std::cout << "     ";
        }
    }
    std::cout << "\n";
}

// Helper function to print yearly X-axis labels
void CandlestickPlot::printYearlyXAxis(const std::vector<Candlestick> &candlesticks)
{
    // Extract the start year from the first candlestick's date
    int startYear = std::stoi(candlesticks.front().date.substr(0, 4));

    // Print year numbers with proper spacing
    std::cout << "       ";
    for (size_t i = 0; i < candlesticks.size(); ++i)
    {
        std::cout << std::setw(5) << (startYear + i);
    }
    std::cout << "\n";
}
