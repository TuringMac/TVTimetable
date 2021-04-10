// TVTimetable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include "Timetable.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("cls");
	cout << "Программа ТВ передач" << endl;

	Timetable* tt = new Timetable("timetable1.txt");

	tt->ReadFromFile();
	tt->Print();
	tt->Add(tt->InputRecoord());
	//tt->Add(2, 2000, "Смак", 12);
	//tt->Add(4, 2200, "Спокойной ночи, малыши");
	tt->Print();
	tt->SaveToFile();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
