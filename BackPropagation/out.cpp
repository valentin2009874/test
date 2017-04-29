#include "out.h"

out::out()
{
	x = vector<double>(2, 0);
	t = vector<double>(1, 0.4);
	x[0] = 1;
	x[1] = 2;
	Net = neural(1, 1, 2, 1.0, 0.001, 500, x, t);
}

double out::roundPrecision(double x)
{
	return x < 0.0 ? ceil(x * pow(10, 5) - 0.5) / pow(10, 5) : floor(x * pow(10, 5) + 0.5) / pow(10, 5);
}

string out::vectorToStr(vector<double> x)
{
	std::stringstream res;
	res << "(";
	for (int i = 0; i < x.size() - 1; ++i)
	{
		res << roundPrecision(x[i]) << ", ";
	}
	res << roundPrecision(x.back()) << ")";
	return res.str();
}

string out::fullInfoTeaching()
{
	Net.teaching();
	std::stringstream res;
	res << "Обучение нейронной сети происходило " << Net.error.size() << " эпох\n";
	res << "В итоге среднеквадратичная погрешность стала равна " << Net.error.back() << ".\n";
	res << "\nШаги обучения:\n";
	for (int i = 0; i < Net.error.size(); ++i)
	{
		res << "Эпоха " << i << ": y = " << vectorToStr(Net.outY[i]) << ", E(" << i << ") = " << roundPrecision(Net.error[i]) << "\r\n";
		res << "Веса: W(скрытый слой) = (\n";
		for (int i = 0; i < Net.N; ++i)
		{
			res << "\t{";
			for (int j = 0; j < Net.J - 1; ++j)
				res << Net.w[0][i][j] << ";";
			res << Net.w[0][i].back();
			res << "},\n";
		}
		res << ")\nВеса: W(выходной слой) = (\n";
		for (int i = 0; i < Net.J; ++i)
		{
			res << "\t{";
			for (int j = 0; j < Net.M - 1; ++j)
				res << Net.w[1][i][j] << ";";
			res << Net.w[1][i].back();
			res << "},\n";
		}
	}
	res << ")\n";
	return res.str();
}