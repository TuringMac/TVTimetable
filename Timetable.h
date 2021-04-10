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
			cout << "Не удалось открыть файл для чтения\n";
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
	bool SaveToFile()
	{
		ofstream out(filename);
		if (!out)
		{
			cout << "Не удалось открыть файл для записи\n";
			return false;
		}
		for (TimetableRow row : rows)
		{
			row.programName = sanitizeString(row.programName);
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
		rows.push_back(row);
	}
	void Add(TimetableRow row)
	{
		rows.push_back(row);
	}
	TimetableRow InputRecoord()
	{
		TimetableRow row;
		row.Id = getId();
		cout << "Введите номер канала:";
		cin >> row.channel;
		cout << "Введите время передачи:";
		cin >> row.time;
		cout << "Введите название программы:";
		cin.ignore();
		getline(cin, row.programName);
		cout << "Введите возрастные ограничения:";
		cin >> row.age;
		return row;
	}
	/// <summary>
	/// FR-04 Сортировка записей в файле
	/// </summary>
	/// <param name="column"></param>
	void Sort(int column)
	{

	}
	/// <summary>
	/// FR-06 Вывести все записи в консоль
	/// </summary>
	void Print()
	{
		cout << "-------- Timetable --------\n";
		for (TimetableRow row : rows)
		{
			cout << row.Id << '\t' << row.channel << '\t' << row.time << '\t' << row.programName << '\t' << row.age << '\n';
		}
		cout << "---------------------------\n";
	}
	/// <summary>
	/// FR-07 Удалить определенную запись
	/// </summary>
	/// <param name="id"></param>
	/// <returns></returns>
	bool Delete(int id)
	{

	}
	/// <summary>
	/// FR-08 Удалить все записи
	/// </summary>
	/// <returns></returns>
	bool Clear()
	{
		rows.clear();
		SaveToFile();
	}
private:
	string filename;
	list<TimetableRow> rows;
	/// <summary>
	/// FR-03 Проверка записи на корректность
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	string sanitizeString(string str)
	{
		str.erase(remove(str.begin(), str.end(), '\t'), str.end());
		return str;
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
};

