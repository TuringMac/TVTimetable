#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

struct TimetableRow {
	int Id;
	int channel;
	int time;
	//char programName[80];
	string programName;
	int age;

	bool operator == (const TimetableRow& row) const
	{
		return Id == row.Id;
	}
};

class Timetable
{
public:
	Timetable(std::string pFilename)
	{
		filename = pFilename;
		std::srand(std::time(nullptr));
	}
	bool ReadFromFile()
	{
		ifstream in(filename);
		if (!in)
		{
			cout << "�� ������� ������� ���� ��� ������\n";
			return false;
		}
		string line;
		rows.clear();
		while (getline(in, line))
		{
			rows.push_back(parseLine(line));
		}
		//std::getline(nameFileout, item_name);
		//getline(ss, name, ' '); //extract first field (until space)
		in.close();
		return true;
	}
	/// <summary>
	/// FR-02 �������� ������ � ����
	/// </summary>
	/// <returns></returns>
	bool SaveToFile()
	{
		ofstream out(filename);
		if (!out)
		{
			cout << "�� ������� ������� ���� ��� ������\n";
			return false;
		}
		for (TimetableRow row : rows)
		{
			out << row.Id << '\t' << row.channel << '\t' << row.time << '\t' << row.programName << '\t' << row.age << '\n';
		}
		out.close();
		return true;
	}
	void Add(int channel, int time, string programName, int age = 0)
	{
		TimetableRow row;
		row.Id = getId();
		row.channel = channel;
		row.time = time;
		row.programName = programName;
		row.age = age;
		row = sanitizeRow(row);
		rows.push_back(row);
	}
	void Add(TimetableRow row)
	{
		row = sanitizeRow(row);
		rows.push_back(row);
	}
	TimetableRow InputRecoord()
	{
		TimetableRow row;
		row.Id = getId();
		cout << "������� ����� ������:";
		cin >> row.channel;
		cout << "������� ����� ��������(��������: 1830 ��� 2115): ";
		cin >> row.time;
		cout << "������� �������� ���������: ";
		cin.get();
		getline(cin, row.programName);
		cout << "������� ���������� �����������: ";
		cin >> row.age; // TODO ���������� ������ �����
		return row;
	}
	/// <summary>
	/// FR-04 ���������� ������� � �����
	/// </summary>
	/// <param name="column"></param>
	void Sort(int column)
	{
		switch (column)
		{
		case 0: rows.sort(compare_id); break;
		case 1: rows.sort(compare_channel); break;
		case 2: rows.sort(compare_time); break;
		case 3: rows.sort(compare_programName); break;
		default: return;
		}
	}
	/// <summary>
	/// FR-06 ������� ��� ������ � �������
	/// </summary>
	void Print()
	{
		cout << "-------- ��������� --------\n";
		for (TimetableRow row : rows)
		{
			cout << row.Id << '\t' << row.channel << '\t' << row.time / 100 << ":" << row.time % 100 << '\t' << row.programName << '\t' << row.age << '\n';
		}
		cout << "---------------------------\n";
	}
	/// <summary>
	/// FR-07 ������� ������������ ������
	/// </summary>
	/// <param name="id"></param>
	/// <returns></returns>
	bool Delete(int id)
	{
		rows.remove(getById(id));
		return true;
	}
	/// <summary>
	/// FR-08 ������� ��� ������
	/// </summary>
	/// <returns></returns>
	bool Clear()
	{
		rows.clear();
		SaveToFile();
		return true;
	}
private:
	string filename;
	list<TimetableRow> rows;
	/// <summary>
	/// FR-03 �������� ������ �� ������������
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	TimetableRow sanitizeRow(TimetableRow row)
	{
		row.programName.erase(remove(row.programName.begin(), row.programName.end(), '\t'), row.programName.end());
		row.time = (row.time / 100) % 24 * 100 + (row.time % 100) % 60;
		row.age = abs(row.age);
		return row;
	}
	int getId()
	{
		int newId = 0;
		for (TimetableRow row : rows)
		{
			if (row.Id > newId)
				newId = row.Id;
		}
		return newId == 0 ? std::rand() : (newId + 1);
	}
	TimetableRow getById(int id)
	{
		for (TimetableRow row : rows)
		{
			if (row.Id == id) return row;
		}
		TimetableRow row;
		return row;
	}
	TimetableRow parseLine(string line)
	{
		istringstream iss(line);
		string part;
		TimetableRow row;
		getline(iss, part, '\t');
		row.Id = stoi(part);
		getline(iss, part, '\t');
		row.channel = stoi(part);
		getline(iss, part, '\t');
		row.time = stoi(part);
		getline(iss, part, '\t');
		row.programName = part;
		getline(iss, part, '\t');
		row.age = stoi(part);

		return row;
	}
	static bool compare_id(const TimetableRow& first, const TimetableRow& second)
	{
		if (first.Id < second.Id) return true;
		else if (first.Id > second.Id) return false;
		else return true;
	}
	static bool compare_channel(const TimetableRow& first, const TimetableRow& second)
	{
		if (first.channel < second.channel) return true;
		else if (first.channel > second.channel) return false;
		else return true;
	}
	static bool compare_time(const TimetableRow& first, const TimetableRow& second)
	{
		if (first.time < second.time) return true;
		else if (first.time > second.time) return false;
		else return true;
	}
	static bool compare_programName(const TimetableRow& first, const TimetableRow& second)
	{
		unsigned int i = 0;
		while ((i < first.programName.length()) && (i < second.programName.length()))
		{
			if (tolower(first.programName[i]) < tolower(second.programName[i])) return true;
			else if (tolower(first.programName[i]) > tolower(second.programName[i])) return false;
			++i;
		}
		return (first.programName.length() < second.programName.length());
	}
};

