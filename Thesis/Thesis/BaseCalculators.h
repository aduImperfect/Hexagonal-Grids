#pragma once
#include <math.h>

#include "BaseEnumerations.h"

double Heuristic(int heuType, double xDiff, double yDiff)
{
  switch (heuType)
  {
  case HeuristicType::HEURISTIC_CHEBYSHEV:
    return fmax(xDiff, yDiff);
    break;
  case HeuristicType::HEURISTIC_MANHATTAN:
    return (xDiff + yDiff);
    break;
  case HeuristicType::HEURISTIC_EUCLIDEAN:
    return sqrt((xDiff*xDiff) + (yDiff*yDiff));
    break;
  case HeuristicType::HEURISTIC_OCTILE:
    return fmin(xDiff, yDiff) * sqrt(2) + fmax(xDiff, yDiff) - fmin(xDiff, yDiff);
    break;
  }

  return -1;
}

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
  std::ostringstream out;
  if (a_value >= 10.00f)
  {
    out << std::fixed << std::setprecision(n - 1) << a_value;
  }
  else
  {
    out << std::fixed << std::setprecision(n) << a_value;
  }
  return out.str();
}
