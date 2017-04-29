#include <iostream>
#include "neural.h"
#include "out.h"
using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");

	// Создание объекта класса нейронной сети и передача его в класс вывода
	out res;

	bool exit = 0;			// Завершения работы программы, когда exit == 1
	do
	{
		cout << "Выберите часть лабораторной 3:";
		cout << "\n0 - выход;";
		cout << "\n1 - запустить обучение;\n";

		int userAns;
		cin >> userAns;
		switch (userAns)
		{
		case 0:
			cout << "\nGoobay!";
			exit = 1;				// Выход из программы
			break;
		case 1:
			cout << res.fullInfoTeaching();
			break;
		default:
			cout << "\nПовторите ввод.";// Что-то не то
			break;
		}
	} while (!exit);


	return 0;
}
