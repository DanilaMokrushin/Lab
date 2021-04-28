#include <iostream>
#include <fstream>
#include <string>
#include "pipe.h"
#include "compressor_station.h"
#include "Utils.h"
#include "unordered_map"
#include "Graph.h"

using namespace std;

void DisplayGraph(unordered_map<int, vector<PCS>>& Graph, unordered_map<int, pipe>& groupP, unordered_map<int, compressor_station>& groupCS)
{
	for (auto& el : Graph)
	{
		cout << "КС с ID " << el.first << " соединен с: ";
		for (auto cs = el.second.begin(); cs != el.second.end(); cs++)
		{
			cout << cs->idCS << " кс длиной " << groupP[cs->idP].length;
			if (cs + 1 != el.second.end()) cout << ", ";
		}
		cout << endl;
	}
}

void dfs(int v, unordered_map<int, vector<PCS>> & g, unordered_map<int, bool> & count, vector<int> & ans) {
	count[v] = true;
	vector<PCS> arr;
	if (g.find(v) != g.end()) {

		arr = g[v];
		for (auto& el : arr) {
			int to = el.idCS;

			if (!count[to])
				dfs(to, g, count, ans);
		}
	}
	ans.push_back(v);
}

void topologicalSort(unordered_map<int, vector<PCS>> & g, unordered_map<int, bool> & count, vector<int> & ans) {
	for (auto& el : g)
	{
		count[el.first] = false;
		for (auto& p1 : el.second)
		{
			count[p1.idCS] = false;
		}
	};
	ans.clear();
	for (auto& el : count)
		if (!el.second)
			dfs(el.first, g, count, ans);
	reverse(ans.begin(), ans.end());
}

bool dfs2(int v, unordered_map<int, vector<PCS>> & g, unordered_map<int, int> & cl, int& cycle_st) {
	if (g.find(v) == g.end())
	{
		return false;
	}
	cl[v] = 1;
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to;

		to = g[v][i].idCS;
		if (cl[to] == 0) {
			if (dfs2(to, g, cl, cycle_st))  return true;
		}
		else if (cl[to] == 1) {
			cycle_st = to;
			return true;
		}
	}
	cl[v] = 2;
	return false;
}

bool searchForCycle(unordered_map<int, vector<PCS>> & graph)
{
	unordered_map<int, int> p;
	int cycle_st, cycle_end;
	for (auto& el : graph)
	{
		p[el.first] = 0;
	}
	cycle_st = -1;
	for (auto& el : p)
		if (dfs2(el.first, graph, p, cycle_st)) break;
	if (cycle_st == -1) return false;
	else return true;
}

void InputGraphFromFile(unordered_map<int, vector<PCS>> & graph, unordered_map<int, pipe> & groupP, unordered_map<int, compressor_station> & groupCS, string str)
{

	ifstream fin;
	fin.open(str + ".txt", ios::in);
	if (!fin.is_open())
		cout << "Файл не может быть открыт!\n";
	else
	{
		int buff;
		groupP.erase(groupP.begin(), groupP.end());
		fin >> buff;
		for (int j = 1; j <= buff; ++j)
		{
			pipe P;
			fin >> P;
			groupP.insert(pair<int, pipe>(P.GetId(), P));
		}

		fin >> buff;
		groupCS.erase(groupCS.begin(), groupCS.end());
		for (int j = 1; j <= buff; ++j)
		{
			compressor_station cs;
			fin >> cs;
			groupCS.insert(pair<int, compressor_station>(cs.GetId(), cs));
		}
		while (fin >> buff)
		{
			int CSid1;
			fin >> CSid1;
			for (int i = 0; i < buff; i++)
			{
				int CSid2;
				fin >> CSid2;
				int Pipeid;
				fin >> Pipeid;
				PCS pair1;
				pair1.idCS = CSid2;
				pair1.idP = Pipeid;
				graph[CSid1].push_back(pair1);
			}
		}

		cout << "Ввели из файла данные" << endl;
		fin.close();
	}

}

void OutputGraphToFile(const unordered_map<int, vector<PCS>> & graph, const unordered_map<int, pipe> & groupP, const unordered_map<int, compressor_station> & groupCS, string str)
{
	ofstream fout;
	fout.open(str + ".txt");
	if (!fout.is_open())
		cout << "Файл не может быть открыт!\n";
	else
	{
		fout << groupP.size() << endl;
		for (auto& P : groupP)
			fout << P.second;
		fout << endl;
		fout << groupCS.size() << endl;
		for (auto& CS : groupCS)
			fout << CS.second;
		fout << endl;
		for (auto& el : graph)
		{
			fout << el.second.size() << " ";
			fout << el.first << " ";
			for (auto cs = el.second.begin(); cs != el.second.end(); cs++)
			{
				fout << cs->idCS << " " << cs->idP << " ";
			}
			fout << endl;
		}

		cout << "Вывели в файл данные" << endl;
		fout.close();
	}
}

void DeleteCSGraph(unordered_map<int, vector<PCS>> & graph, unordered_map<int, compressor_station> & groupCS)
{
	size_t a = 1;
	int idCS1 = -1;
	while (groupCS.find(idCS1) == groupCS.end())
	{
		cout << "Введите Id Кс необходимую отключить: ";
		idCS1 = GetCorrectNumber(a, groupCS.size());
	}
	if (graph.find(idCS1) != graph.end())
	{
		graph.erase(idCS1);
	}
	for (auto el = graph.begin(); el != graph.end(); el++)
	{
		for (auto it = 0; it < el->second.size(); it++)
		{
			if (el->second[it].idCS == idCS1) {
				el->second.erase(el->second.begin() + it);
			}
		}
	}
	cout << "Удален!" << endl;
}

unordered_map<int, bool> CountVertex(unordered_map<int, vector<PCS>> & graph)
{
	unordered_map<int, bool> count;
	for (auto& iter : graph)
	{
		count[iter.first] = false;
		for (auto& v : iter.second)
		{
			count[v.idCS] = false;
		}
	}
	return count;
}
//Алгоритм Дейкстры
void ShortPath(unordered_map<int, vector<PCS>> & graph, unordered_map<int, pipe> & pipe_group)
{
	cout << "Введите id КС - начало пути: ";
	int id_from = GetCorrectNumber(1u, compressor_station::GetMaxID());
	cout << "Введите id КС - конец пути: ";
	int id_to = GetCorrectNumber(1u, compressor_station::GetMaxID());
	if (graph.find(id_from) != graph.end())
	{
		unordered_map <int, int> distance;
		unordered_map <int, bool> passed;
		unordered_map<int, bool> count = CountVertex(graph);
		unordered_map<int, int>p;

		for (auto i = graph.begin(); i != graph.end(); i++)
		{
			int i1 = i->first;
			distance[i1] = INT_MAX;
			passed[i1] = false;
			for (auto j : i->second)
			{
				distance[j.idCS] = INT_MAX;
				passed[j.idCS] = false;
			}
		}
		distance[id_from] = 0;
		int index = 0;
		for (auto j = count.begin(); j != count.end(); j++)
		{
			int min = INT_MAX;
			for (auto i = count.begin(); i != count.end(); i++)
			{
				int i1 = i->first;
				if (!passed[i1] && distance[i1] <= min)
				{
					min = distance[i1];
					index = i1;
				}
			}
			passed[index] = true;
			for (auto i = graph[index].begin(); i != graph[index].end(); i++)
			{
				int i1 = i->idCS;
				if (!passed[i1] && distance[index] != INT_MAX && distance[index] + pipe_group[i1].length < distance[i1])
				{
					distance[i1] = distance[index] + pipe_group[i1].length;
					p[i1] = index;
				}

			}
		}
		cout << "Наикратчайший путь:" << endl;
		if (distance[id_to] != INT_MAX)
		{
			cout << id_from << " -> " << id_to << " = " << distance[id_to] << endl;
			vector <int> path;
			for (int vertex = id_to; vertex != id_from; vertex = p[vertex])
				path.push_back(vertex);
			path.push_back(id_from);
			reverse(path.begin(), path.end());
			cout << "Путь: ";
			for (auto i = path.begin(); i != path.end(); i++)
			{
				if (i + 1 != path.end()) cout << *i << " -> ";
				else cout << *i;
			}
		}
		else cout << id_from << " -> " << id_to << " - пути нет";
	}
	else cout << "Невозможно!" << endl;
}