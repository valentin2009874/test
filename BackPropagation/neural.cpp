#include "neural.h"

neural::neural(int NT, int MT, int JT, double etaT, double allowableErrorT, int maxEpochT, vector<double> xT, vector<double> tT)
{
	N = NT + 1;
	M = MT;
	J = JT + 1;
	eta = etaT;
	maxEpoch = maxEpochT;
	allowableError = allowableErrorT;
	x = xT;
	t = tT;
}

neural::neural()
{
	N = 0;
	M = 0;
	J = 0;
}

bool neural::teaching()
{
	resetW();
	double rmsError;

	for (int epoch = 0; epoch <= maxEpoch; ++epoch)
	{
		vector<double> outHidden;					// Выход скрытого слоя или вход последнего слоя
		outY.push_back(vector<double>());		// Выход выходного слоя или y
		vector<vector<double>> delta;				// delta для каждого слоя
		delta.push_back(vector<double>());          // для скрытого
		delta.push_back(vector<double>());          // для выходного
		rmsError = 0;

		// Расчет выхода для скрытого слоя
		for (int j = 0; j < J; ++j)
		{
			double net = w[0][0][j];
			for (int i = 1; i < N; ++i)
			{
				net += w[0][i][j] * x[i];
			}
			double outNet = fa(net);
			outHidden.push_back(outNet);
		}

		// Расчет выхода для выходного слоя
		for (int j = 0; j < M; ++j)
		{
			double net = w[1][0][j];
			for (int i = 1; i < J; ++i)
			{
				net += w[1][i][j] * outHidden[i];
			}
			double y = fa(net);
			outY[epoch].push_back(y);

			// Подсчет дельт для выходного слоя
			delta[1].push_back(dfa(net) * (t[j] - y));
			rmsError += pow(t[j] - y, 2);
		}

		// Подсчет дельт для скрытого слоя
		for (int j = 0; j < J; ++j)
		{
			double net = w[0][0][j];
			for (int i = 1; i < N; ++i)
			{
				net += w[0][i][j] * x[i];
			}
			double wDelta = 0;
			for (int i = 0; i < M; ++i)
			{
				wDelta += w[1][j][i] * delta[1][i];
			}
			delta[0].push_back(dfa(net) * wDelta);
		}

		for (int j = 0; j < J; ++j)
		{
			// корректировка весов скрытого слоя
			for (int i = 1; i < N; ++i)
				w[0][i][j] += eta * x[i] * delta[0][j];
		}

		for (int j = 0; j < M; ++j)
		{
			//корректировка весов выходного слоя
			for (int i = 1; i < J; ++i)
				w[1][i][j] += eta * outHidden[i] * delta[1][j];
		}

		rmsError = sqrt(rmsError);
		error.push_back(rmsError);

		if (rmsError < allowableError)
			return false;
	}
	return true;
}

void neural::resetW()
{
	w = vector<vector<vector<double>>>(2, vector<vector<double>>());
	for (int i = 0; i < N; ++i) // Добавляем все веса скрытого слоя 
		w[0].push_back(vector<double>(J, 0));

	for (int i = 0; i < J; ++i) // Добавляем все веса последнего слоя 
		w[1].push_back(vector<double>(M, 0));

	for (int k = 0; k<2; ++k)
	{
		for (int i = 0; i < w[k].size(); ++i)
			for (int j = 0; j < w[k][i].size(); ++j) // установим веса смещения случайными значениями [0; 1) 
				w[k][i][j] = ((double)rand() / (RAND_MAX));
	}
}

double neural::fa(double net)
{
	return (1 - exp(net)) / (1 + exp(net));
}

double neural::dfa(double net)
{
	return (1 - pow(fa(net), 2)) / 2;
}



