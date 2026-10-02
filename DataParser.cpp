// DataParser.cpp
#include "DataParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// Constructor that initializes the file path and country code for the DataParser
DataParser::DataParser(const std::string &filePath, const std::string &countryCode)
    : filePath(filePath), countryCode(countryCode) {}

// Method to retrieve the parsed temperature data in candlestick format
std::vector<Candlestick> DataParser::getTemperatureData() const
{
    // Return the previously computed candlestick data
    return candlestickData;
}

// Method to parse the CSV file and extract hourly temperature data for the given country code
void DataParser::parse()
{
    // Open the CSV file for reading
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    // Read the header line to find the relevant country column
    std::string line, header;
    std::getline(file, header);

    // Use a string stream to parse the header line
    std::istringstream headerStream(header);
    std::string column;
    int countryIndex = -1;
    int index = 0;

    // Find the column index for the specified country code
    while (std::getline(headerStream, column, ','))
    {
        if (column == countryCode + "_temperature")
        {
            countryIndex = index;
            break;
        }
        ++index;
    }

    // If the country code is not found in the header, print an error message and return
    if (countryIndex == -1)
    {
        std::cerr << "Country code not found in file header." << std::endl;
        return;
    }

    // Read the data lines from the CSV file
    while (std::getline(file, line))
    {
        // Use a string stream to parse each line
        std::istringstream lineStream(line);
        std::string date, value;
        std::vector<std::string> values;

        // Split the line by commas and store the values in a vector
        while (std::getline(lineStream, value, ','))
        {
            values.push_back(value);
        }

        // If the vector size is greater than the country index, extract the temperature data
        if (values.size() > static_cast<size_t>(countryIndex))
        {
            std::string datetime = values[0];                          // The first value is the date and time
            double temperature = std::stod(values[countryIndex]);      // Convert the temperature value to double
            hourlyData[datetime.substr(0, 10)].push_back(temperature); // Group the temperature data by day
        }
    }

    // Close the CSV file
    file.close();
}

// Method to compute daily candlestick data from the parsed hourly data
std::vector<Candlestick> DataParser::computeDailyCandlesticks()
{
    std::vector<Candlestick> candlesticks;
    double previousClose = 0.0; // Store the closing value of the previous day

    // Iterate through each day's hourly data
    for (const auto &entry : hourlyData)
    {
        const std::vector<double> &temps = entry.second;             // Get the temperatures for the day
        Candlestick candle;                                          // Create a new candlestick object
        candle.date = entry.first;                                   // Set the date of the candlestick
        candle.open = previousClose;                                 // Set the open value to the previous day's close
        candle.high = *std::max_element(temps.begin(), temps.end()); // Find the highest temperature
        candle.low = *std::min_element(temps.begin(), temps.end());  // Find the lowest temperature
        candle.close = temps.back();                                 // Set the close value to the last temperature of the day

        previousClose = candle.close;   // Update the previous close value
        candlesticks.push_back(candle); // Add the candlestick to the vector
    }
    return candlesticks;
}

// Method to compute monthly candlestick data from daily candlestick data
std::vector<Candlestick> DataParser::computeMonthlyCandlesticks()
{
    std::map<std::string, std::vector<double>> monthlyData; // Map to store temperature data grouped by month

    // Group the daily temperature data by month
    for (const auto &entry : hourlyData)
    {
        std::string month = entry.first.substr(0, 7); // Extract the year and month (YYYY-MM)
        monthlyData[month].insert(monthlyData[month].end(), entry.second.begin(), entry.second.end());
    }

    std::vector<Candlestick> candlesticks;
    double previousClose = 0.0; // Store the closing value of the previous month

    // Iterate through each month's temperature data
    for (const auto &entry : monthlyData)
    {
        const std::vector<double> &temps = entry.second;             // Get the temperatures for the month
        Candlestick candle;                                          // Create a new candlestick object
        candle.date = entry.first + "-01";                           // Set the date of the candlestick to the first day of the month
        candle.open = previousClose;                                 // Set the open value to the previous month's close
        candle.high = *std::max_element(temps.begin(), temps.end()); // Find the highest temperature
        candle.low = *std::min_element(temps.begin(), temps.end());  // Find the lowest temperature
        candle.close = temps.back();                                 // Set the close value to the last temperature of the month

        previousClose = candle.close;   // Update the previous close value
        candlesticks.push_back(candle); // Add the candlestick to the vector
    }
    return candlesticks;
}

// Method to compute yearly candlestick data from monthly candlestick data
std::vector<Candlestick> DataParser::computeYearlyCandlesticks()
{
    std::map<std::string, std::vector<double>> yearlyData; // Map to store temperature data grouped by year

    // Group the monthly temperature data by year
    for (const auto &entry : hourlyData)
    {
        std::string year = entry.first.substr(0, 4); // Extract the year (YYYY)
        yearlyData[year].insert(yearlyData[year].end(), entry.second.begin(), entry.second.end());
    }

    std::vector<Candlestick> candlesticks;
    double previousClose = 0.0; // Store the closing value of the previous year

    // Iterate through each year's temperature data
    for (const auto &entry : yearlyData)
    {
        const std::vector<double> &temps = entry.second;             // Get the temperatures for the year
        Candlestick candle;                                          // Create a new candlestick object
        candle.date = entry.first + "-01-01";                        // Set the date of the candlestick to the first day of the year
        candle.open = previousClose;                                 // Set the open value to the previous year's close
        candle.high = *std::max_element(temps.begin(), temps.end()); // Find the highest temperature
        candle.low = *std::min_element(temps.begin(), temps.end());  // Find the lowest temperature
        candle.close = temps.back();                                 // Set the close value to the last temperature of the year

        previousClose = candle.close;   // Update the previous close value
        candlesticks.push_back(candle); // Add the candlestick to the vector
    }
    return candlesticks;
}
