#ifndef CANDLESTICK_H
#define CANDLESTICK_H
#include <iostream>
#include <string>

// The Candlestick class represents a candlestick used for technical analysis in weather data
class Candlestick
{
public:
    std::string date; // Date of the candlestick
    double open;      // Opening temperature for the time frame
    double high;      // Highest temperature for the time frame
    double low;       // Lowest temperature for the time frame
    double close;     // Closing temperature for the time frame

    // Default constructor initializing values to zero
    Candlestick() : open(0), high(0), low(0), close(0) {}

    // Parameterized constructor to initialize candlestick data with specific values
    Candlestick(const std::string &date, double open, double high, double low, double close)
        : date(date), open(open), high(high), low(low), close(close) {}

    // Method to display candlestick data in a formatted row (for debugging purposes)
    void displayRow() const;
};

#endif // CANDLESTICK_H
