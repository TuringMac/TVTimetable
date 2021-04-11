// TVTimetable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "date.h"
#include <windows.h>
#include "Timetable.h"

using namespace std;

void LogMessage(string msg)
{
	string filename = "Timetable.log";
	ofstream out(filename, ios_base::app);
	if (!out)
	{
		cout << "Не удалось открыть Лог-файл для записи" << endl;
	}
	out << msg << endl;
	out.close();
}

int Menu(int page = 0)
{
	int i = 0;
	int menu = -1;
	system("cls");
	cout << "---=== Главное меню ===---" << endl;
	//cout << "[" << i++ << "]" << " Вывести программу передач на сегодня" << endl;
	i++;
	cout << "[" << i++ << "]" << " Вывести отслеживаемые программы" << endl;
	cout << "[" << i++ << "]" << " Отсортировать отслеживаемые программы по времени" << endl;
	cout << "[" << i++ << "]" << " Добавить отслеживаемую программу" << endl;
	cout << "[" << i++ << "]" << " Удалить отслеживаемую программу" << endl;
	cout << "[" << i++ << "]" << " Очистить список" << endl;
	cout << "[" << i++ << "]" << " Сохранить" << endl;
	cout << "[" << i++ << "]" << " Редактировать запись" << endl;
	cout << "[" << i++ << "]" << " Отсортировать отслеживаемые программы по алфавиту" << endl;

	cout << "[-1]" << " Выход" << endl;
	cout << " Укажите пункт меню: ";
	cin >> menu;
	return menu;
}

void back()
{
	cout << "Нажмите Ввод, чтобы вернутсья в меню...";
	cin.ignore();
	cin.get();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("cls");
	string curDate = date::format("%F %T", chrono::system_clock::now());

	cout << "Запущено: " << curDate << endl << "Программа ТВ передач" << endl;
	LogMessage(curDate); // FR-01 Сохранение даты и времени запуска приложения

	Timetable* tt = new Timetable("timetable1.txt");
	tt->ReadFromFile();
	bool terminate = false;
	while (!terminate)
	{
		int id = -1;
		switch (Menu())
		{
		//case 0: break;
		case 1:
			system("cls");
			tt->Print();
			back();
			break;
		case 2:
			system("cls");
			tt->Sort(2);
			tt->Print();
			back();
			break;
		case 3:
			system("cls");
			tt->Add(tt->InputRecoord());
			tt->Print();
			back();
			break;
		case 4:
			system("cls");
			tt->Print();
			cout << "Укажить ИД записи для удаления";
			cin >> id;
			tt->Delete(id);
			tt->SaveToFile();
			cout << "Очищено" << endl;
			back();
			break;
		case 5:
			system("cls");
			tt->Clear();
			tt->SaveToFile();
			cout << "Очищено" << endl;
			back();
			break;
		case 6:
			system("cls");
			tt->SaveToFile();
			cout << "Сохранено" << endl;
			back();
			break;
		case 7:
			system("cls");
			tt->Print();
			cout << "Укажите Ид записи для редактирования: ";
			cin >> id;
			tt->Edit(id);
			system("cls");
			tt->Print();
			back();
			break;
		case 8:
			system("cls");
			tt->Sort(3);
			tt->Print();
			back();
			break;
		default:
			terminate = true;
		}
	}
}
