#ifndef PREDICTOR_H
#define PREDICTOR_H

#include "Candlestick.h"
#include <vector>

// Function to predict future temperatures
std::vector<Candlestick> predictFutureTemperatures(const std::vector<Candlestick> &candlesticks, int windowSize, int futurePeriods, char periodType);

#endif // PREDICTOR_H
