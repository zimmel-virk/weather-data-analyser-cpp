# Weather Data Analyser & Forecasting System — C++

A command-line C++ application for analysing historical European temperature data using candlestick-style summaries, text-based visualisation, interactive filtering and moving-average forecasting.

The project processes hourly temperature observations from **1980 to 2019** and allows the user to examine weather trends at daily, monthly and yearly frequencies.

All original C++ source files, coursework documents and the supplied weather dataset are preserved unchanged.

## Project Overview

The application is organised around four main tasks:

1. compute candlestick data from historical temperatures;
2. display candlestick information using text-based charts;
3. filter temperature data interactively;
4. predict future temperature values using a moving-average method.

The program is built using object-oriented C++ and separates parsing, candlestick representation, filtering, plotting, orchestration and prediction into dedicated components.

## Dataset

The supplied dataset is:

```text
weather_data_EU_1980-2019_temp_only.csv
```

It contains hourly temperature observations for European countries over the period:

```text
1980–2019
```

The application lists the following country codes as available:

```text
AT BE BG CH CZ DE DK EE ES FI FR GB GR HR HU IE IT LT LU LV NL NO PL PT RO SE SI SK
```

The source code reports a total of:

```text
350,640 entries
```

The user chooses a country code, and the parser locates the corresponding column named in the form:

```text
<COUNTRY>_temperature
```

For example:

```text
GB_temperature
```

## Candlestick Representation

Temperature observations are aggregated into candlestick-style records containing:

```text
Date
Open
High
Low
Close
```

The application supports:

- daily candlesticks;
- monthly candlesticks;
- yearly candlesticks.

In the implementation used by `WeatherAnalyzer`, `DataParser` groups hourly readings by day, month or year and creates `Candlestick` objects for each period.

The project also contains a separate `CandlestickCalculator` class with calculation routines for daily, monthly and yearly aggregation.

## Initial 40-Year Analysis

When the program starts, it:

1. displays the available country codes;
2. asks the user to choose a country;
3. parses the CSV data for that country;
4. computes yearly candlesticks;
5. prints approximately 40 years of yearly data;
6. plots the yearly data as text-based candlestick charts;
7. displays summary statistics.

The statistics include:

- mean temperature;
- maximum temperature;
- minimum temperature.

## Text-Based Candlestick Charts

`CandlestickPlot` renders the weather data directly in the terminal.

The chart uses:

```text
|      High/Low stalk
----   Open/Close values
```

Charts are dynamically scaled to the temperature range.

To keep terminal output manageable, `WeatherAnalyzer` displays candlestick records in groups of up to:

```text
30 entries per graph
```

The plotting code provides separate x-axis formatting for:

- daily data;
- monthly data;
- yearly data.

## Date and Frequency Filtering

The interactive workflow allows users to enter a date range.

Accepted examples shown by the program include:

```text
2018
1990-02
2019-12-22
```

The user then chooses a frequency:

```text
d = daily
m = monthly
y = yearly
```

The selected candlestick data is filtered to the requested range and displayed in both:

- tabular form;
- text-based candlestick charts.

The user may also limit the number of entries displayed.

## Additional Filters

`Filters` provides several additional ways to explore the data.

### Month Across All Years

A selected month can be extracted across the historical period.

Example:

```text
01
07
12
```

### Minimum Temperature

Keeps candlesticks meeting the selected minimum-temperature condition.

### Maximum Temperature

Keeps candlesticks meeting the selected maximum-temperature condition.

### Temperature Range

Filters observations using both minimum and maximum temperature limits.

### No Filter

Returns the complete current candlestick set.

## Future Temperature Prediction

The project includes a forecasting function:

```cpp
predictFutureTemperatures(...)
```

The user chooses:

- prediction frequency;
- moving-average window size;
- number of future periods.

Supported prediction periods are:

```text
d = days
m = months
y = years
```

The prediction algorithm calculates moving averages of recent candlestick:

- open;
- high;
- low;
- close;

values.

Each generated prediction is appended to a working copy of the data so that subsequent future periods can use earlier predictions in the moving-average window.

Predicted values are then:

- printed as a table;
- plotted using the same candlestick visualisation system.

## Main Classes and Components

### `Candlestick`

Represents one weather candlestick.

Fields include:

```cpp
std::string date;
double open;
double high;
double low;
double close;
```

It also contains a formatted row-display method.

### `DataParser`

Responsible for:

- opening the weather CSV;
- locating the selected country's temperature column;
- parsing hourly temperature observations;
- grouping data by date;
- computing daily candlesticks;
- computing monthly candlesticks;
- computing yearly candlesticks.

### `CandlestickCalculator`

Provides separate methods for:

```cpp
calculateDailyCandlesticks(...)
calculateMonthlyCandlesticks(...)
calculateYearlyCandlesticks(...)
```

### `CandlestickPlot`

Renders text-based terminal charts and frequency-specific x-axes.

### `Filters`

Implements:

```cpp
filterByDateRange(...)
filterByMonthAcrossYears(...)
filterByMinTemperature(...)
filterByMaxTemperature(...)
filterByTemperatureRange(...)
noFilter(...)
```

### `Predictor`

Implements moving-average future-temperature prediction.

### `WeatherAnalyzer`

Coordinates the complete interactive application workflow:

- country selection;
- parsing;
- yearly overview;
- plotting;
- filtering;
- statistics;
- forecasting.

## Repository Structure

```text
weather-data-analyser-cpp/
├── README.md
├── .gitignore
├── ORIGINAL_FILES_VERIFIED.txt
├── main.cpp
├── Candlestick.cpp
├── Candlestick.h
├── CandlestickCalculator.cpp
├── CandlestickCalculator.h
├── CandlestickPlot.cpp
├── CandlestickPlot.h
├── DataParser.cpp
├── DataParser.h
├── Filters.cpp
├── Filters.h
├── Predictor.cpp
├── Predictor.h
├── WeatherAnalyzer.cpp
├── WeatherAnalyzer.h
├── weather_data_EU_1980-2019_temp_only.csv
├── report.pdf
├── code.pdf
└── compilation.txt
```

## Building

The project uses the C++ standard library and does not require an external framework.

A typical build command is:

```bash
g++ -std=c++17 \
  main.cpp \
  Candlestick.cpp \
  CandlestickCalculator.cpp \
  CandlestickPlot.cpp \
  DataParser.cpp \
  Filters.cpp \
  Predictor.cpp \
  WeatherAnalyzer.cpp \
  -o weather_analyzer
```

Run with:

```bash
./weather_analyzer
```

The CSV file should remain in the same working directory because the original program loads:

```text
weather_data_EU_1980-2019_temp_only.csv
```

using a relative path.

## Technologies and Concepts

- C++
- Object-Oriented Programming
- CSV parsing
- historical time-series analysis
- data aggregation
- terminal visualisation
- filtering
- descriptive statistics
- moving-average forecasting
- STL vectors, maps and algorithms

## Coursework Documents

The original project also contains:

```text
report.pdf
code.pdf
compilation.txt
```

These files are retained exactly as supplied.

## Original-File Preservation

All original C++ source files, headers, dataset files, PDFs and text files were copied byte-for-byte without changing their contents.

Only repository-support files were added:

```text
README.md
.gitignore
ORIGINAL_FILES_VERIFIED.txt
```

Operating-system metadata such as `.DS_Store` is excluded.

## Author

**Zimmel Javed Virk**  
BSc Computer Science — University of London
