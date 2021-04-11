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
		cout << "�� ������� ������� ���-���� ��� ������" << endl;
	}
	out << msg << endl;
	out.close();
}

int Menu(int page = 0)
{
	int i = 0;
	int menu = -1;
	system("cls");
	cout << "---=== ������� ���� ===---" << endl;
	//cout << "[" << i++ << "]" << " ������� ��������� ������� �� �������" << endl;
	i++;
	cout << "[" << i++ << "]" << " ������� ������������� ���������" << endl;
	cout << "[" << i++ << "]" << " ������������� ������������� ��������� �� �������" << endl;
	cout << "[" << i++ << "]" << " �������� ������������� ���������" << endl;
	cout << "[" << i++ << "]" << " ������� ������������� ���������" << endl;
	cout << "[" << i++ << "]" << " �������� ������" << endl;
	cout << "[" << i++ << "]" << " ���������" << endl;
	cout << "[" << i++ << "]" << " ������������� ������" << endl;
	cout << "[" << i++ << "]" << " ������������� ������������� ��������� �� ��������" << endl;

	cout << "[-1]" << " �����" << endl;
	cout << " ������� ����� ����: ";
	cin >> menu;
	return menu;
}

void back()
{
	cout << "������� ����, ����� ��������� � ����...";
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

	cout << "��������: " << curDate << endl << "��������� �� �������" << endl;
	LogMessage(curDate); // FR-01 ���������� ���� � ������� ������� ����������

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
			cout << "������� �� ������ ��� ��������";
			cin >> id;
			tt->Delete(id);
			tt->SaveToFile();
			cout << "�������" << endl;
			back();
			break;
		case 5:
			system("cls");
			tt->Clear();
			tt->SaveToFile();
			cout << "�������" << endl;
			back();
			break;
		case 6:
			system("cls");
			tt->SaveToFile();
			cout << "���������" << endl;
			back();
			break;
		case 7:
			system("cls");
			tt->Print();
			cout << "������� �� ������ ��� ��������������: ";
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
