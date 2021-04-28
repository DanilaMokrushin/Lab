
#include <iostream>
#include <fstream>
#include <string>
#include "pipe.h"
#include "compressor_station.h"
#include "Utils.h"
#include "unordered_map"
#include "Graph.h"

using namespace std;

void Menu()
{
	system("CLS");
	cout << "1.Добавить трубу" << endl
		<< "2.Добавит КС" << endl
		<< "3.Просмотр трубы" << endl
		<< "4.Просмотр КС" << endl
		<< "5.Редактировать трубу" << endl
		<< "6.Редактировать КС" << endl
		<< "11.Удалить трубу" << endl
		<< "12.Удалить КС" << endl
		<< "13.Поиск КС по названию" << endl
		<< "14.Поиск трубы по признаку 'в ремонте'" << endl
		<< "15.Пакетное редактирование труб" << endl
		<< "16.Создать газотранспортную сеть" << endl
		<< "17.Топологическая сортировка" << endl
		<< "18.Загрузить газотранспортную сеть" << endl
		<< "19.Сохранить газотранспортную сеть" << endl
		<< "20.Показать газотранспортную сети" << endl
		<< "21.Удалить газотранспортную сети" << endl
		<< "22.Удалить КС из газотранспортной сети" << endl
		<< "23.Кратчайший путь" << endl
		<< "0.Выход" << endl;
};

void PrintPipe(unordered_map<int, pipe>& groupP)
{
	if (groupP.size() > 0)
	{
		for (auto& P : groupP)
			cout << P.second << endl;
		system("pause");
	}
	else { cout << "ВВедите трубу!"; }
}

void PrintCS(unordered_map<int, compressor_station> & groupCS)
{
	if (groupCS.size() > 0)
	{
		for (auto& CS : groupCS)
			cout << CS.second << endl;
		system("pause");
	}
	else { cout << "ВВедите трубу!"; }
}

void EditPipe(pipe & pipe_i)
{
	cout << "Изменить работу трубы?(да - 1, нет - 0):";
	bool i = GetCorrectNumber(0, 1);
	if (i == 1) {
		pipe_i.work = !pipe_i.work;
	}
}

void EditCS(compressor_station & CS_i)
{
	cout << "Добавить рабочую КС?(да - 1, нет - 0):";
	bool i = GetCorrectNumber(-1, 2);
	if (i == 1 && CS_i.manufactory > CS_i.manufactory_w) {
		CS_i.manufactory_w++;
	}
	cout << "Убрать рабочую КС?(да - 1, нет - 0):";
	i = GetCorrectNumber(-1, 2);
	if (i == 1 && CS_i.manufactory > CS_i.manufactory_w) {
		CS_i.manufactory_w--;
	}
}

void DelPipe(unordered_map<int, pipe> & groupP)
{
	size_t a = 1;
	if (groupP.size() > 0)
	{
		for (auto& P : groupP)
			cout << P.second << endl;
		system("pause");
	}
	else { cout << "ВВедите трубу!"; }

	if (groupP.size() > 0) {
		int number;
		do {
			cout << "Введите ID КС, которую нужно удалить: ";
			number = GetCorrectNumber(a, groupP.size());
		} while (groupP.find(number) == groupP.end());
		groupP.erase(groupP.find(number));
	}
}

void DelCS(unordered_map<int, compressor_station> & CS_i)
{
	size_t a = 1;
	if (CS_i.size() > 0)
	{
		for (auto& P : CS_i)
			cout << P.second << endl;
		system("pause");
	}
	else { cout << "ВВедите трубу!"; }

	if (CS_i.size() > 0) {
		int number;
		do {
			cout << "Введите ID КС, которую нужно удалить: ";
			number = GetCorrectNumber(a, CS_i.size());
		} while (CS_i.find(number) == CS_i.end());
		CS_i.erase(CS_i.find(number));
	}
}

pipe& SelectPipe(unordered_map<int, pipe> & g)
{
	size_t a = 1;
	cout << "Введите индекс: ";
	unsigned int index = GetCorrectNumber(a, g.size());
	return g[index];
}

compressor_station& SelectCS(unordered_map<int, compressor_station> & g)
{
	size_t a = 1;
	cout << "Введите индекс: ";
	unsigned int index = GetCorrectNumber(a, g.size());
	return g[index];
}

template<typename PC, typename T>
using FilterCS = bool(*)(PC & CS, T param);

bool CheckByName(compressor_station & CS, string param)
{
	return CS.name == param;
}

template<typename PC, typename T>
vector <int> FindByFilter(unordered_map<int, PC> & group, FilterCS<PC, T> f, T param)
{
	vector <int> res;
	res.reserve(group.size());
	for (auto& pipe : group)
	{
		if (f(pipe.second, param))
			res.push_back(pipe.first);
	}
	return res;
}

bool CheckByWork(pipe & P, bool param)
{
	return P.work == param;
}

bool CheckByLength(pipe & P, float param)
{
	return P.length == param;
}

bool CheckByDiam(pipe & P, int param)
{
	return P.diameter == param;
}

int main()
{
	unordered_map<int, pipe> groupP;
	unordered_map<int, compressor_station> groupCS;
	unordered_map<int, vector<PCS>> Graph;
	size_t a = 1;
	setlocale(LC_ALL, "Russian");
	while (true) {
		Menu();
		cout << "Выберите действие - ";
		switch (GetCorrectNumber(0, 23))
		{
		case 1:
		{
			pipe P;
			cin >> P;
			groupP.insert(pair<int, pipe>(P.GetId(), P));
			break;
		}
		case 2:
		{
			compressor_station CS;
			cin >> CS;
			groupCS.insert(pair<int, compressor_station>(CS.GetId(), CS));
			break;
		}
		case 3:
		{
			PrintPipe(groupP);
			break;
		}
		case 4:
		{
			PrintCS(groupCS);
			break;
		}
		case 5:
		{
			if (groupP.size() > 0) { EditPipe(SelectPipe(groupP)); }
			else { cout << "Введите трубу!"; }
			break;
		}
		case 6:
		{
			if (groupCS.size() > 0) { EditCS(SelectCS(groupCS)); }
			else { cout << "Введите КС!"; }
			break;
		}
		case 11:
		{
			DelPipe(groupP);
			break;
		}
		case 12:
			DelCS(groupCS);
			break;
		case 13:
		{
			string name;
			cout << "Введите название КС: ";
			cin.ignore();
			getline(cin, name);
			for (int i : FindByFilter(groupCS, CheckByName, name))
				cout << groupCS[i];
			system("pause");
			break;
		}
		case 14:
		{
			bool name;
			cout << "Искать рабочие трубы(1), не рабочие(0): ";
			cin >> name;
			for (int i : FindByFilter(groupP, CheckByWork, name))
				cout << groupP[i];
			system("pause");
			break;
		}
		case 15:
		{
			bool j;
			cout << "Чтобы найти трубы по параметру введите 1, по промежутку - 0: ";
			j = GetCorrectNumber(0, 1);
			if (j) {
				cout << "Выберете параметр поиска" << endl
					<< "1. Длина" << endl
					<< "2. Работа" << endl;
				switch (GetCorrectNumber(1, 3))
				{
				case 1:
				{
					cout << "Введите длину, необходимую заменить - ";
					float c = GetCorrectNumber(1.0, 100000.0);
					cout << "Введите новую длину - ";
					float b = GetCorrectNumber(1.0, 100000.0);
					for (int i : FindByFilter(groupP, CheckByLength, c))
						groupP[i].length = b;
				}
				break;
				case 2:
				{
					cout << "Введите работу, необходимую заменить - ";
					bool c = GetCorrectNumber(0, 1);
					cout << "Введите новую работу - ";
					bool b = GetCorrectNumber(0, 1);
					for (int i : FindByFilter(groupP, CheckByWork, c))
						groupP[i].work = b;
				}
				break;
				}
			}
			else {
				int a, b;
				int right = groupP.size();
				cout << "Введите начальный индекс: ";
				a = GetCorrectNumber(0, right);
				cout << "Введите конечный индекс: ";
				b = GetCorrectNumber(a, right);
				cout << "Выберете параметр изменения" << endl
					<< "1. Длинна" << endl
					<< "2. Ширина" << endl
					<< "3. Работа" << endl
					<< "0. Вернутся обратно" << endl;
				switch (GetCorrectNumber(0, 3)) {
				case 1:
				{
					cout << "Введите длинну - ";
					float c = GetCorrectNumber(0, 1000000);
					for (int i = a; i < b; i++) {
						groupP[i].length = c;
					}
					break;
				}
				case 2:
				{
					cout << "Введите диаметр - ";
					int c = GetCorrectNumber(0, 1000000);
					for (int i = a; i < b; i++) {
						groupP[i].diameter = c;
					}
					break;
				}
				case 3:
				{
					cout << "Введите работу - ";
					bool c = GetCorrectNumber(0, 1);
					for (int i = a; i < b; i++) {
						groupP[i].work = c;
					}
					break;
				}
				}
			}
		}
		break;
		case 16:
		{
			int i;
			int j = 0;
			PCS pcs;
			PrintPipe(groupP);
			PrintCS(groupCS);
			if (groupCS.size() > 1 && groupP.size() > 0)
			{
				cout << "Введите колество труб: ";
				i = GetCorrectNumber(a, groupP.size());
				while (i > 0) {
					cout << "Введите id КС, от которой идёт труба: ";
					int idCS1 = GetCorrectNumber(a, groupCS.size());
					cout << "Введите id КС, в которую идёт труба: ";
					pcs.idCS = GetCorrectNumber(a, groupCS.size());
					cout << "Введите id трубы: ";
					pcs.idP = GetCorrectNumber(a, groupP.size());

					Graph[idCS1].push_back(pcs);
					i--;
				}
				DisplayGraph(Graph, groupP, groupCS);
			}
			else
			{
				cout << "Невозможно выполнить операцию";
			};
			system("pause");
			break;
		}
		case 17:
		{
			if (!searchForCycle(Graph))
			{
				unordered_map<int, bool> count;
				vector<int> ans;
				topologicalSort(Graph, count, ans);
				for (auto index = ans.begin(); index != ans.end(); index++)
				{
					cout << *index;
					if (index + 1 != ans.end()) cout << " -> ";
				}
				system("pause");
			}
			else
			{
				cout << "Граф цикличный!" << endl;
			}
			system("pause");
			break;
		}
		case 18:
		{
			string str;
			cout << "Введите название файла: ";
			cin >> str;
			InputGraphFromFile(Graph, groupP, groupCS, str);

			system("pause");
			break;
		}
		case 19:
		{
			string str;
			cout << "Введите название файла: ";
			cin >> str;
			OutputGraphToFile(Graph, groupP, groupCS, str);

			system("pause");
			break;
		}
		case 20:
		{
			DisplayGraph(Graph, groupP, groupCS);
			system("pause");
			break;
		}
		case 21:
		{
			Graph.clear();
			break;
		}
		case 22:
		{
			PrintCS(groupCS);
			DeleteCSGraph(Graph, groupCS);
			system("pause");
			break;
		}
		case 23:
		{
			ShortPath(Graph, groupP);
			system("pause");
			break;
		}
		case 0:
			exit(0);
			break;
		default:
			cout << "Введите верное число!" << endl;
			break;
		}
	}
}