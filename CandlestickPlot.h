// CandlestickPlot.h
#ifndef CANDLESTICKPLOT_H
#define CANDLESTICKPLOT_H

#include <vector>
#include "Candlestick.h"

// The CandlestickPlot class provides methods to plot candlestick data using text-based charts
class CandlestickPlot
{
public:
    // Function to plot the weather candlesticks as a text-based chart
    // Parameters:
    // - candlesticks: A vector of Candlestick objects to be plotted
    // - chartHeight: The height of the text chart in lines
    // - frequency: The time period frequency ('d' for daily, 'm' for monthly, 'y' for yearly)
    static void plot(const std::vector<Candlestick> &candlesticks, int chartHeight, char frequency);

private:
    // Helper function to print daily X-axis labels on the chart
    // Parameters:
    // - candlesticks: A vector of Candlestick objects used to determine the labels
    static void printDailyXAxis(const std::vector<Candlestick> &candlesticks);

    // Helper function to print monthly X-axis labels on the chart
    // Parameters:
    // - candlesticks: A vector of Candlestick objects used to determine the labels
    static void printMonthlyXAxis(const std::vector<Candlestick> &candlesticks);

    // Helper function to print yearly X-axis labels on the chart
    // Parameters:
    // - candlesticks: A vector of Candlestick objects used to determine the labels
    static void printYearlyXAxis(const std::vector<Candlestick> &candlesticks);
};

#endif // CANDLESTICKPLOT_H
