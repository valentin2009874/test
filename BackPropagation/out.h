#pragma once
#include <vector>
#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <sstream>
#include "neural.h"
using namespace std;
class out
{
public:
	string fullInfoTeaching();
	out();

private:
	string vectorToStr(vector<double> x);
	double roundPrecision(double x);
	neural Net;
	vector<double> x;
	vector<double> t;
};
