#pragma once
#include <fstream>
using std::ofstream;
#include <iostream>
#include <list>
using std::cout;
using std::endl;
#include <string>

struct TimetableRow {
	int Id;
	int channel;
	int time;
	char programName[80];
	int age;
};

class Timetable
{
public:
	bool ReadFromFile(char filePath[])
	{
		return true;
	}
	bool SaveToFile(char filePath[])
	{
		ofstream out("timetable.txt");
		if (!out)
		{
			cout << "�� ������� ������� ���� ��� ������\n";
			return false;
		}
		for (TimetableRow row : rows)
		{
			out.write((char*)row.Id, sizeof(row.Id));
			out.write((char*)row.channel, sizeof(row.channel));
			out.write((char*)row.time, sizeof(row.time));
			out.write((char*)row.programName, sizeof(row.programName));
			out.write((char*)row.age, sizeof(row.age));
		}
		out.close();
		return true;
	}
	/// <summary>
	/// FR-04 ���������� ������� � �����
	/// </summary>
	/// <param name="column"></param>
	void Sort(int column)
	{

	}
	/// <summary>
	/// FR-06 ������� ��� ������ � �������
	/// </summary>
	void Print()
	{

	}
private:
	std::list<TimetableRow> rows;
	/// <summary>
	/// FR-03 �������� ������ �� ������������
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	char* sanitizeString(char* str)
	{
		// TODO check string for \t entrance
	}

	
};

