#include "compressor_station.h"
#include"Utils.h"
using namespace std;

int compressor_station::MaxID = 0;

int compressor_station::GetId()
{
	return id;
}

compressor_station::compressor_station()
{
	id = ++MaxID;
}

unsigned int compressor_station::GetMaxID()
{
	return MaxID;
}

istream& operator >> (istream& in, compressor_station& CS_i)
{
	cout << "Введите название - ";
	cin.ignore();
	getline(cin, CS_i.name);
	cout << "Введите количество цехов - ";
	CS_i.manufactory = GetCorrectNumber(0, 100000);
	cout << "Введите количество рабочих цехов - ";
	CS_i.manufactory_w = GetCorrectNumber(0, 100000);
	while (CS_i.manufactory_w > CS_i.manufactory)
	{
		cout << "Введите колич. раб. цехов меньше общего количества: ";
		CS_i.manufactory_w = GetCorrectNumber(0, 100000);
	}
	cout << "Введите эффективность - ";
	CS_i.efficiency = GetCorrectNumber(0.0, 1.0);
	return in;
}

ostream& operator << (ostream& out, const compressor_station& CS_i)
{
	cout << CS_i.id << endl;
	cout << "Компрессорная станция:" << endl;
	cout << "Название - " << CS_i.name << endl;
	cout << "Количество цехов - " << CS_i.manufactory << endl;
	cout << "Количество рабочих цехов - " << CS_i.manufactory_w << endl;
	cout << "Эффективность - " << CS_i.efficiency << endl;
	return out;
}

ofstream& operator << (ofstream& OutFile, const compressor_station& CS_i)
{
	OutFile << endl << CS_i.id << endl << CS_i.name << endl << CS_i.manufactory << endl << CS_i.manufactory_w << endl << CS_i.efficiency;
	return OutFile;
};

ifstream& operator >> (ifstream& InFile, compressor_station& CS_i)
{
	InFile >> CS_i.id >> CS_i.name >> CS_i.manufactory >> CS_i.manufactory_w >> CS_i.efficiency;
	return InFile;
};