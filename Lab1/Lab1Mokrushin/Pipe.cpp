#include "pipe.h"
#include "unordered_map"
#include"Utils.h"
using namespace std;

int pipe::MaxID = 0;

int pipe::GetId()
{
	return id;
}

pipe::pipe()
{
	id = ++MaxID;
}

istream& operator >> (istream& in, pipe& pipe_i)
{
	cout << "Введите длину(м) - ";
	pipe_i.length = GetCorrectNumber(0, 200);
	cout << "Введите диаметр(мм) - ";
	pipe_i.diameter = GetCorrectNumber(0, 200);
	cout << "Введите 1, если труба работает или 0 - если труба не работает - ";
	pipe_i.work = GetCorrectNumber(-1, 2);
	return in;
}

ostream& operator << (ostream& out, const pipe& pipe_i)
{
	cout << pipe_i.id << endl;
	cout << "Труба:" << endl;
	cout << "Идентификатор - " << pipe_i.id << endl;
	cout << "Длина(м) - " << pipe_i.length << endl;
	cout << "Диаметр(мм) - " << pipe_i.diameter << endl;
	cout << (pipe_i.work ? "Работает" : "Не работает") << endl << endl;
	return out;
}

ofstream & operator << (ofstream & OutFile, const pipe & pipe_i)
{
	OutFile << endl << pipe_i.id << endl << pipe_i.length << endl << pipe_i.diameter << endl << pipe_i.work;
	return OutFile;
}

ifstream& operator >> (ifstream & InFile, pipe & pipe_i)
{
	InFile >> pipe_i.id >> pipe_i.length >> pipe_i.diameter >> pipe_i.work;
	return InFile;
};