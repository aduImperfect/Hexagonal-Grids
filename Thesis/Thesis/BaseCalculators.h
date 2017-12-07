///////////////////////////////////////////////////////////////////////////////////////
/// All content (c) 2017 DigiPen Institute of Technology, all rights reserved
/// FILE: BaseCalculators.h
/// AUTHOR(S): Aditya Subramanian <aditya.subramanian@digipen.edu>
///////////////////////////////////////////////////////////////////////////////////////

#ifndef BASE_CALCULATORS_H
#define BASE_CALCULATORS_H
//Including the different required standard library for math and base headers which contain the base enumerations.
#include <math.h>
#include "BaseEnumerations.h"

/*
Calculates the heuristic based on the type of heuristic to be calculated.
Parameters to the function:
heuType : const HeuristicType - the heuristic type.
xDiff : const double - the x difference.
yDiff : const double - the y difference.
Returns from the function:
heuristicVal : double - return the calculated heuristic value.
This function takes in the heuristic type along with the x (x2-x1) and y (y2-y1) differences which is then used to calculate the new heuristic value.
It returns the calculated heuristic value.
*/
double /*heuristicVal*/ Heuristic(const HeuristicType heuType, const double xDiff, const double yDiff)
{
	switch (heuType)
	{
	case HeuristicType::HEURISTIC_CHEBYSHEV:
		//max((x2-x1), (y2-y1)).
		return fmax(xDiff, yDiff);
		break;
	case HeuristicType::HEURISTIC_MANHATTAN:
		//(x2-x1) + (y2-y1).
		return (xDiff + yDiff);
		break;
	case HeuristicType::HEURISTIC_EUCLIDEAN:
		//sqrt((x2-x1)^2 + (y2-y1)^2).
		return sqrt((xDiff*xDiff) + (yDiff*yDiff));
		break;
	case HeuristicType::HEURISTIC_OCTILE:
		//(min((x2-x1), (y2-y1)) * sqrt(2)) + max((x2-x1), (y2-y1)) - min((x2-x1), (y2-y1)).
		return fmin(xDiff, yDiff) * sqrt(2) + fmax(xDiff, yDiff) - fmin(xDiff, yDiff);
		break;
	}

	//If no heuristic return -1.
	return -1;
}

/*
Changes a specific value to string with a set number of precision.
Parameters to the function:
a_value : const T - the value to be stringified which is of type T.
n : const int - the number of precision.
Returns from the function:
valueString : std::string - return the stringified value.
This function takes in a value of a random type (T) and the number of precision and finds its stringified form.
It returns the value in string form with n degrees of precision.
*/
template <typename T>
std::string /*valueString*/ to_string_with_precision(const T a_value, const int n = 6)
{
  std::ostringstream out;
  //If the value is greater than 10.00f, the numbers of precision used is n-1, else numbers of precision used is n.
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
#endif