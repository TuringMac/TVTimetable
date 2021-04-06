#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include <string>

using namespace std;

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
			out << row.Id << '\t' << row.channel << '\t' << row.time << '\t' << row.programName << '\t' << row.age << '\n';
			/*
			out.write((char*)row.Id, sizeof(row.Id));
			out.write((char*)row.channel, sizeof(row.channel));
			out.write((char*)row.time, sizeof(row.time));
			out.write((char*)row.programName, sizeof(row.programName));
			out.write((char*)row.age, sizeof(row.age));
			*/
		}
		out.close();
		return true;
	}
	void Add(int channel, int time, std::string programName, int age = 0)
	{
		TimetableRow row;
		row.Id = getId();
		row.channel = channel;
		row.time = time;
		//row.programName = programName; // TODO
		row.age = age;
		rows.push_back(row);
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
	char* sanitizeString(char* str)
	{
		// TODO check string for \t entrance
	}
	int getId()
	{
		return std::rand();
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
		//row.programName = part; // TODO
		getline(iss, part, '\t');
		row.age = stoi(part);

		return row;
	}
};

