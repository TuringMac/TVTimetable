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

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("cls");
	string curDate = date::format("%F %T", std::chrono::system_clock::now());

	cout << "Запущено: " << curDate << endl << "Программа ТВ передач" << endl;
	LogMessage(curDate); // FR-01 Сохранение даты и времени запуска приложения

	Timetable* tt = new Timetable("timetable1.txt");

	tt->ReadFromFile();
	tt->Print();
	tt->Add(tt->InputRecoord());
	//tt->Add(2, 2000, "Смак", 12);
	//tt->Add(4, 2200, "Спокойной ночи, малыши");
	tt->Print();
	tt->SaveToFile();
}
