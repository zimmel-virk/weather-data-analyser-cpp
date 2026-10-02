// DataParser.h
#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <string>
#include <map>
#include <vector>
#include "Candlestick.h"

// The DataParser class is responsible for parsing temperature data from a CSV file
// and computing candlestick data (daily, monthly, and yearly)
class DataParser
{
private:
    std::string filePath;                                  // Path to the CSV file containing weather data
    std::string countryCode;                               // Country code to filter the data (e.g., "GB" for Great Britain)
    std::map<std::string, std::vector<double>> hourlyData; // Map to store hourly temperature data grouped by date
    std::vector<Candlestick> candlestickData;              // Vector to store computed candlestick data

public:
    // Constructor to initialize the file path and country code
    // Parameters:
    // - filePath: Path to the CSV file
    // - countryCode: Two-character country code for filtering the data
    DataParser(const std::string &filePath, const std::string &countryCode);

    // Method to parse the CSV file and extract hourly temperature data for the specified country
    void parse();

    // Method to compute daily candlestick data from the parsed hourly data
    // Returns: A vector of Candlestick objects representing daily candlesticks
    std::vector<Candlestick> computeDailyCandlesticks();

    // Method to compute monthly candlestick data from daily candlestick data
    // Returns: A vector of Candlestick objects representing monthly candlesticks
    std::vector<Candlestick> computeMonthlyCandlesticks();

    // Method to compute yearly candlestick data from monthly candlestick data
    // Returns: A vector of Candlestick objects representing yearly candlesticks
    std::vector<Candlestick> computeYearlyCandlesticks();

    // Method to retrieve the parsed temperature data in candlestick format
    // Returns: A vector of Candlestick objects representing the temperature data
    std::vector<Candlestick> getTemperatureData() const;
};

#endif // DATAPARSER_H
