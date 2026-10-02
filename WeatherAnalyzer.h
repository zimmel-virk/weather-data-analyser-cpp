#ifndef WEATHERANALYZER_H
#define WEATHERANALYZER_H

#include <iostream>          // For standard input/output operations
#include <string>            // For using the string class
#include <vector>            // For using vectors to store data
#include <map>               // For using maps to store key-value pairs
#include <iomanip>           // For formatted output
#include <numeric>           // For numeric operations such as accumulate
#include <algorithm>         // For using std::max_element and std::min_element functions
#include "DataParser.h"      // Header file for data parsing
#include "CandlestickPlot.h" // Header file for plotting candlestick charts
#include "Filters.h"         // Header file for filtering candlestick data
#include "Predictor.h"       // Header file for predicting future temperature data

class WeatherAnalyzer
{
public:
    // This function lists the available country codes from the dataset for the user's reference
    void displayAvailableCountries()
    {
        std::cout << "Total 350640 entries\n";
        std::cout << "Country codes available: [ AT BE BG CH CZ DE DK EE ES FI FR GB GR HR HU IE IT LT LU LV NL NO PL PT RO SE SI SK ]\n";
    }

    // Function to prompt the user for a date input and return it as a string
    // Parameters:
    // - prompt: The message to display when asking for input
    std::string promptDate(const std::string &prompt)
    {
        std::string date; // Variable to store the date input
        std::cout << prompt;
        std::cin >> date; // Get the user input
        return date;      // Return the entered date
    }

    // Function to prompt the user to choose a frequency for plotting (daily, monthly, or yearly)
    // Returns the frequency character entered by the user
    char promptFrequency()
    {
        char freq; // Variable to store the frequency input
        std::cout << "Enter frequency (y(yearly), m(monthly), d(daily)): ";
        std::cin >> freq; // Get the user input
        return freq;      // Return the entered frequency
    }

    // Function to calculate and display the mean, maximum, and minimum temperatures from the candlestick data
    // Parameters:
    // - candlesticks: A vector of Candlestick objects containing temperature data
    void displayStats(const std::vector<Candlestick> &candlesticks)
    {
        // Calculate the mean temperature by summing the close values and dividing by the number of entries
        double meanTemp = std::accumulate(candlesticks.begin(), candlesticks.end(), 0.0,
                                          [](double sum, const Candlestick &c) { return sum + c.close; }) /
                          candlesticks.size();

        // Find the maximum temperature by comparing the high values of all candlesticks
        double maxTemp = std::max_element(candlesticks.begin(), candlesticks.end(),
                                          [](const Candlestick &a, const Candlestick &b) { return a.high < b.high; })
                             ->high;

        // Find the minimum temperature by comparing the low values of all candlesticks
        double minTemp = std::min_element(candlesticks.begin(), candlesticks.end(),
                                          [](const Candlestick &a, const Candlestick &b) { return a.low < b.low; })
                             ->low;

        // Display the calculated statistics
        std::cout << "\n[**] Mean Temperature: " << meanTemp << "°C";
        std::cout << "\n[**] Max Temperature: " << maxTemp << "°C";
        std::cout << "\n[**] Min Temperature: " << minTemp << "°C\n";
    }

    // Function to plot multiple graphs with a limit of 30 entries per graph
    // Parameters:
    // - candlesticks: A vector of Candlestick objects to be plotted
    // - chartHeight: The height of the chart to be displayed
    // - frequency: The frequency of the data (daily, monthly, or yearly)
    // Function to plot multiple graphs with a limit of 30 entries per graph
    // Displays only a final summary after all graphs are plotted
    void plotMultipleGraphs(const std::vector<Candlestick> &candlesticks, int chartHeight, char frequency)
    {
        const int maxEntriesPerGraph = 30;         // Maximum number of entries to display per graph
        size_t totalEntries = candlesticks.size(); // Total number of candlesticks

        // Plot all graphs in subsets of maxEntriesPerGraph
        size_t startIndex = 0;
        while (startIndex < totalEntries)
        {
            size_t endIndex = std::min(startIndex + maxEntriesPerGraph, totalEntries);
            std::vector<Candlestick> subCandlesticks(candlesticks.begin() + startIndex, candlesticks.begin() + endIndex);

            // Call the plot function to display the current subset of candlesticks
            CandlestickPlot::plot(subCandlesticks, chartHeight, frequency);

            startIndex += maxEntriesPerGraph;
        }

        // Display the final summary once after all graphs are plotted
        std::cout << "\n============================\n";
        std::cout << "Summary:\n";
        displayStats(candlesticks);

        std::cout << "\nLegend:\n";
        std::cout << "'|' : High/Low stalk\n";
        std::cout << "'----' : Open/Close values\n";

        std::cout << "\nNote:\n";
        std::cout << "The Open/Close values are represented as horizontal lines ('----'), and the High/Low values are shown as vertical lines ('|').\n";
    }

    // Function to apply additional filters to the candlestick data based on user input
    // Parameters:
    // - candlesticks: A vector of Candlestick objects to be filtered
    // - frequency: The frequency of the data (daily, monthly, or yearly)
    void applyAdditionalFilters(std::vector<Candlestick> &candlesticks, char frequency)
    {
        int choice; // Variable to store user's choice for filter options
        do
        {
            // Display filter options to the user
            std::cout << "\nSelect a filter option:\n";
            std::cout << "1. Filter by Month Across All Years\n";
            std::cout << "2. Filter by Minimum Temperature\n";
            std::cout << "3. Filter by Maximum Temperature\n";
            std::cout << "4. Filter by Temperature Range\n";
            std::cout << "5. No Filter (Display All Data)\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice; // Get the user's choice

            std::vector<Candlestick> filteredCandlesticks; // Vector to store the filtered candlestick data

            // Apply the filter based on the user's choice
            switch (choice)
            {
            case 1:
            {
                // Filter by a specific month across all years
                std::string targetMonth;
                std::cout << "Enter month (MM): ";
                std::cin >> targetMonth;
                filteredCandlesticks = Filters::filterByMonthAcrossYears(candlesticks, targetMonth);
                break;
            }
            case 2:
            {
                // Filter by minimum temperature
                double minTemp;
                std::cout << "Enter minimum temperature: ";
                std::cin >> minTemp;
                filteredCandlesticks = Filters::filterByMinTemperature(candlesticks, minTemp);
                break;
            }
            case 3:
            {
                // Filter by maximum temperature
                double maxTemp;
                std::cout << "Enter maximum temperature: ";
                std::cin >> maxTemp;
                filteredCandlesticks = Filters::filterByMaxTemperature(candlesticks, maxTemp);
                break;
            }
            case 4:
            {
                // Filter by a temperature range (minimum and maximum)
                double minTemp, maxTemp;
                std::cout << "Enter minimum temperature: ";
                std::cin >> minTemp;
                std::cout << "Enter maximum temperature: ";
                std::cin >> maxTemp;
                filteredCandlesticks = Filters::filterByTemperatureRange(candlesticks, minTemp, maxTemp);
                break;
            }
            case 5:
                // No filter applied, return all data
                filteredCandlesticks = Filters::noFilter(candlesticks);
                break;
            default:
                // Handle invalid input
                std::cerr << "Invalid choice. Please try again.\n";
                continue;
            }

            // Display the filtered data in a table format
            std::cout << "\nOpen, High, Low, and Close values for the filtered range:\n";
            std::cout << std::setw(12) << "Date"
                      << std::setw(12) << "Open/°C"
                      << std::setw(12) << "Close/°C"
                      << std::setw(12) << "High/°C"
                      << std::setw(12) << "Low/°C" << std::endl;

            // Iterate over the filtered candlesticks and display each row
            for (const auto &candle : filteredCandlesticks)
            {
                candle.displayRow();
            }

            // Plot the filtered data on a chart
            plotMultipleGraphs(filteredCandlesticks, 20, frequency);

            // Ask if the user wants to apply more filters
            char moreFilters;
            std::cout << "\nWould you like to apply more filters? (y/n): ";
            std::cin >> moreFilters;
            if (moreFilters == 'n' || moreFilters == 'N')
            {
                break; // Exit the loop if the user chooses not to apply more filters
            }

        } while (true);
    }

    void run()
    {
        // Display the list of available countries to the user
        displayAvailableCountries();

        // Prompt the user to enter a country code
        std::string countryCode;
        std::cout << "Enter country code: ";
        std::cin >> countryCode;

        // Load the data from the specified CSV file for the chosen country
        std::string filePath = "weather_data_EU_1980-2019_temp_only.csv";
        DataParser parser(filePath, countryCode);
        parser.parse(); // Parse the data

        // === Task1 CODE STARTS HERE ===
        // Compute and display yearly candlestick data for the past 40 years
        std::vector<Candlestick> fullData = parser.computeYearlyCandlesticks();
        std::cout << "\nDisplaying data for 40 years:\n";

        // Print table headers for the candlestick data
        std::cout << std::setw(12) << "Date"
                  << std::setw(12) << "Open/°C"
                  << std::setw(12) << "Close/°C"
                  << std::setw(12) << "High/°C"
                  << std::setw(12) << "Low/°C" << std::endl;

        // Iterate through the yearly candlestick data and display each row
        for (const auto &candle : fullData)
        {
            candle.displayRow();
        }

        // Plot the yearly candlestick data
        plotMultipleGraphs(fullData, 20, 'y');

        // === Task1 CODE ENDS HERE ===

        // Prompt the user to decide whether to apply filtering to the data
        char startFiltering;
        std::cout << "\nWould you like to start filtering? (y/n): ";
        std::cin >> startFiltering;

        if (startFiltering == 'y' || startFiltering == 'Y')
        {
            // Prompt the user to enter the start and end dates for filtering
            std::string startDate = promptDate(" Enter start date (inclusive, e.g., 2018, 1990-02, 2019-12-22): ");
            std::string endDate = promptDate("Enter end date (exclusive, e.g., 2018, 1990-02, 2019-12-22): ");

            // Prompt the user to select the frequency for plotting
            char freq = promptFrequency();

            // Compute candlestick data based on the chosen frequency
            std::vector<Candlestick> candlesticks;
            if (freq == 'd')
            {
                candlesticks = parser.computeDailyCandlesticks();
            }
            else if (freq == 'm')
            {
                candlesticks = parser.computeMonthlyCandlesticks();
            }
            else if (freq == 'y')
            {
                candlesticks = parser.computeYearlyCandlesticks();
            }
            else
            {
                std::cerr << "Invalid frequency entered. Exiting.\n";
                return;
            }

            // Filter the candlestick data based on the specified date range
            auto filteredCandlesticks = Filters::filterByDateRange(candlesticks, startDate, endDate);

            // Prompt the user to specify how many entries to display
            int numEntries;
            std::cout << " How many entries do you want to display? (Enter 0 to display all): ";
            std::cin >> numEntries;

            // Limit the number of displayed entries to the specified number
            if (numEntries == 0 || numEntries > filteredCandlesticks.size())
            {
                numEntries = filteredCandlesticks.size();
            }

            // Resize the filtered candlestick data to the desired number of entries
            filteredCandlesticks.resize(numEntries);

            // Display the filtered data
            std::cout << "\nOpen, High, Low, and Close values for the selected range:\n";
            std::cout << std::setw(12) << "Date"
                      << std::setw(12) << "Open/°C"
                      << std::setw(12) << "Close/°C"
                      << std::setw(12) << "High/°C"
                      << std::setw(12) << "Low/°C" << std::endl;

            for (const auto &candle : filteredCandlesticks)
            {
                candle.displayRow();
            }

            // Plot the filtered data
            plotMultipleGraphs(filteredCandlesticks, 20, freq);

            // Display the total number of entries plotted
            std::cout << "\nTotal entries plotted: " << filteredCandlesticks.size() << "\n";

            // Ask the user if they want to apply additional filters after displaying the filtered data
            char moreFilters;
            std::cout << "\nWould you like to apply more filters? (y/n): ";
            std::cin >> moreFilters;

            if (moreFilters == 'y' || moreFilters == 'Y')
            {
                // If the user wants more filters, call the applyAdditionalFilters function
                applyAdditionalFilters(filteredCandlesticks, freq);
            }
            else
            {
                // If the user does not want more filters, display an exit message
                std::cout << "\nExiting filtering process.\n";
            }

            // Prompt the user to decide whether they want to predict future temperatures
            std::cout << "Would you like to predict future temperatures? (y/n): ";
            char predictChoice;
            std::cin >> predictChoice;

            // Check the user's response to the prediction prompt
            if (predictChoice == 'y' || predictChoice == 'Y')
            {
                // If the user chooses to predict, prompt them to select the prediction type
                std::cout << "Select prediction type: (d = days, m = months, y = years): ";
                char periodType;
                std::cin >> periodType;

                // Variables to store the moving average window size and the number of future periods to predict
                int windowSize, futurePeriods;
                std::cout << "Enter moving average window size: ";
                std::cin >> windowSize;
                std::cout << "Enter number of future periods to predict: ";
                std::cin >> futurePeriods;

                // Create a vector to hold the temperature data used for predictions
                std::vector<Candlestick> temperatureData;

                // Determine which candlestick data to use based on the selected prediction type
                if (periodType == 'd')
                {
                    // If the prediction type is daily, use the daily candlestick data
                    temperatureData = parser.computeDailyCandlesticks();
                }
                else if (periodType == 'm')
                {
                    // If the prediction type is monthly, use the monthly candlestick data
                    temperatureData = parser.computeMonthlyCandlesticks();
                }
                else if (periodType == 'y')
                {
                    // If the prediction type is yearly, use the yearly candlestick data
                    temperatureData = parser.computeYearlyCandlesticks();
                }

                // Call the predictFutureTemperatures function to generate predictions
                auto predictions = predictFutureTemperatures(temperatureData, windowSize, futurePeriods, periodType);

                // Display the predicted data in a table format
                std::cout << "\nPredicted Data:\n";
                std::cout << std::setw(12) << "Date"
                          << std::setw(12) << "Open/°C"
                          << std::setw(12) << "Close/°C"
                          << std::setw(12) << "High/°C"
                          << std::setw(12) << "Low/°C" << std::endl;

                // Iterate over the predictions and display each row
                for (const auto &pred : predictions)
                {
                    pred.displayRow();
                }

                // Plot the predicted data using the plotMultipleGraphs function
                plotMultipleGraphs(predictions, 20, periodType);
            }
        }
    }
};

#endif // WEATHERANALYZER_H
