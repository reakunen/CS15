#include "equals.h"
#include <cmath>
#include <iostream>

using namespace std;

bool equals(double a, double b)
{
    if (fabs(a - b) < pow(10, -12))
    {
        return true;
    }
    return false;
}
