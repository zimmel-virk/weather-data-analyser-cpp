#include "Candlestick.h"
#include <iostream>
#include <iomanip>

// Method to display candlestick data in a formatted row with specific column widths
void Candlestick::displayRow() const
{
    // Output the date and candlestick values (open, close, high, low) with proper spacing using setw
    std::cout << std::setw(12) << date
              << std::setw(10) << open
              << std::setw(10) << close
              << std::setw(10) << high
              << std::setw(10) << low
              << std::endl;
}
