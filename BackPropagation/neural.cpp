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
		vector<double> outHidden;					// ����� �������� ���� ��� ���� ���������� ����
		outY.push_back(vector<double>());		// ����� ��������� ���� ��� y
		vector<vector<double>> delta;				// delta ��� ������� ����
		delta.push_back(vector<double>());          // ��� ��������
		delta.push_back(vector<double>());          // ��� ���������
		rmsError = 0;

		// ������ ������ ��� �������� ����
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

		// ������ ������ ��� ��������� ����
		for (int j = 0; j < M; ++j)
		{
			double net = w[1][0][j];
			for (int i = 1; i < J; ++i)
			{
				net += w[1][i][j] * outHidden[i];
			}
			double y = fa(net);
			outY[epoch].push_back(y);

			// ������� ����� ��� ��������� ����
			delta[1].push_back(dfa(net) * (t[j] - y));
			rmsError += pow(t[j] - y, 2);
		}

		// ������� ����� ��� �������� ����
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
			// ������������� ����� �������� ����
			for (int i = 1; i < N; ++i)
				w[0][i][j] += eta * x[i] * delta[0][j];
		}

		for (int j = 0; j < M; ++j)
		{
			//������������� ����� ��������� ����
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
	for (int i = 0; i < N; ++i) // ��������� ��� ���� �������� ���� 
		w[0].push_back(vector<double>(J, 0));

	for (int i = 0; i < J; ++i) // ��������� ��� ���� ���������� ���� 
		w[1].push_back(vector<double>(M, 0));

	for (int k = 0; k<2; ++k)
	{
		for (int i = 0; i < w[k].size(); ++i)
			for (int j = 0; j < w[k][i].size(); ++j) // ��������� ���� �������� ���������� ���������� [0; 1) 
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



