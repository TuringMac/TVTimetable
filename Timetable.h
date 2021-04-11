#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

const string DATE_TIME_FORMAT = "%Y-%m-%d %H:%M";

struct TimetableRow {
	int Id = -1;
	int channel = 0;
	chrono::system_clock::time_point time;
	//char programName[80];
	string programName;
	int age = -1;

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
	/// <summary>
	/// FR-02 Добавить запись в файл
	/// </summary>
	/// <returns></returns>
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
			out << row.Id << '\t' << row.channel << '\t' << date::format(DATE_TIME_FORMAT, row.time) << '\t' << row.programName << '\t' << row.age << '\n';
		}
		out.close();
		return true;
	}
	void Add(int channel, chrono::system_clock::time_point time, string programName, int age = 0)
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
		return InputRecoord(row);
	}
	TimetableRow InputRecoord(TimetableRow& row)
	{
		if (row.Id == -1)
			row.Id = getId();
		string input;
		cout << "Введите номер канала";
		if (row.channel != 0)
			cout << "[" << row.channel << "]";
		cout << ": ";
		cin.get();
		getline(cin, input);
		if (!input.empty()) {
			std::istringstream stream(input);
			stream >> row.channel;
		}
		cout << "Введите время передачи(Например: 1830 или 2115)";
		//if (row.time.time_since_epoch() == default)
		cout << "[" << date::format(DATE_TIME_FORMAT, row.time) << "]";
		cout << ": ";
		cin.get();
		getline(cin, input);
		if (!input.empty()) {
			tm tm = {};
			std::istringstream stream(input);
			stream >> std::get_time(&tm, DATE_TIME_FORMAT.c_str());
			row.time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
		}
		cout << "Введите название программы";
		if (!row.programName.empty())
			cout << "[" << row.programName << "]";
		cout << ": ";
		//cin.get();
		getline(cin, input);
		if (!input.empty()) {
			row.programName = input;
		}
		cout << "Введите возрастные ограничения";
		if (row.age != -1)
			cout << "[" << row.age << "]";
		cout << ": ";
		//cin.get();
		getline(cin, input);
		if (!input.empty()) {
			std::istringstream stream(input);
			stream >> row.age;
		}
		return row;
	}
	/// <summary>
	/// FR-04 Сортировка записей в файле
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
	/// FR-06 Вывести все записи в консоль
	/// </summary>
	void Print()
	{
		cout << "-------- Избранное --------\n";
		for (TimetableRow row : rows)
		{
			cout << row.Id << '\t' << row.channel << '\t' << date::format(DATE_TIME_FORMAT, row.time) << '\t' << row.programName << '\t' << row.age << '\n';
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
		rows.remove(getById(id));
		return true;
	}
	/// <summary>
	/// FR-08 Удалить все записи
	/// </summary>
	/// <returns></returns>
	bool Clear()
	{
		rows.clear();
		SaveToFile();
		return true;
	}
	/// <summary>
	/// FR-05 Изменить определенную запись
	/// </summary>
	/// <param name="line"></param>
	/// <returns></returns>
	bool Edit(int id)
	{
		TimetableRow& row = getById(id);
		InputRecoord(row);
		return true;
	}
private:
	string filename;
	list<TimetableRow> rows;
	/// <summary>
	/// FR-03 Проверка записи на корректность
	/// </summary>
	/// <param name="row"></param>
	/// <returns></returns>
	TimetableRow sanitizeRow(TimetableRow row)
	{
		row.programName.erase(remove(row.programName.begin(), row.programName.end(), '\t'), row.programName.end());
		//row.time = (row.time / 100) % 24 * 100 + (row.time % 100) % 60;
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
	TimetableRow& getById(int id)
	{
		for (TimetableRow& row : rows)
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
		tm tm = {};
		stringstream ss(part);
		ss >> std::get_time(&tm, DATE_TIME_FORMAT.c_str());
		row.time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
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

