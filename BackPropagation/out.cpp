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
	res << "�������� ��������� ���� ����������� " << Net.error.size() << " ����\n";
	res << "� ����� ������������������ ����������� ����� ����� " << Net.error.back() << ".\n";
	res << "\n���� ��������:\n";
	for (int i = 0; i < Net.error.size(); ++i)
	{
		res << "����� " << i << ": y = " << vectorToStr(Net.outY[i]) << ", E(" << i << ") = " << roundPrecision(Net.error[i]) << "\r\n";
		res << "����: W(������� ����) = (\n";
		for (int i = 0; i < Net.N; ++i)
		{
			res << "\t{";
			for (int j = 0; j < Net.J - 1; ++j)
				res << Net.w[0][i][j] << ";";
			res << Net.w[0][i].back();
			res << "},\n";
		}
		res << ")\n����: W(�������� ����) = (\n";
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