#include <iostream>
#include "neural.h"
#include "out.h"
using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");

	// �������� ������� ������ ��������� ���� � �������� ��� � ����� ������
	out res;

	bool exit = 0;			// ���������� ������ ���������, ����� exit == 1
	do
	{
		cout << "�������� ����� ������������ 3:";
		cout << "\n0 - �����;";
		cout << "\n1 - ��������� ��������;\n";

		int userAns;
		cin >> userAns;
		switch (userAns)
		{
		case 0:
			cout << "\nGoobay!";
			exit = 1;				// ����� �� ���������
			break;
		case 1:
			cout << res.fullInfoTeaching();
			break;
		default:
			cout << "\n��������� ����.";// ���-�� �� ��
			break;
		}
	} while (!exit);


	return 0;
}
