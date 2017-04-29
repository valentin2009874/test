#pragma once
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <sstream>
using namespace std;

class neural
{
public:
	neural(int NT, int MT, int JT, double etaT, double allowableErrorT, int maxEpochT, vector<double> xT, vector<double> tT);
	neural();
	vector<double> t, x;

	vector<vector<vector<double>>> w;
	vector<double> error;
	vector<vector<double>> outY;
	double allowableError;
	int N, M, J, maxEpoch;
	double eta;

	double fa(double net);
	double dfa(double net);
	bool teaching();
	void resetW();
};


