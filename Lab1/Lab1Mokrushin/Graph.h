#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "pipe.h"
#include "compressor_station.h"
#include "Utils.h"
#include "unordered_map"

using namespace std;

struct PCS
{
	int idP;
	int idCS;
};

void DisplayGraph(unordered_map<int, vector<PCS>>& Graph, unordered_map<int, pipe>& groupP, unordered_map<int, compressor_station>& groupCS);

void dfs(int v, unordered_map<int, vector<PCS>>& g, unordered_map<int, bool>& count, vector<int>& ans);

void topologicalSort(unordered_map<int, vector<PCS>>& g, unordered_map<int, bool>& count, vector<int>& ans);

bool dfs2(int v, unordered_map<int, vector<PCS>>& g, unordered_map<int, int>& cl, int& cycle_st);

bool searchForCycle(unordered_map<int, vector<PCS>>& graph);

void InputGraphFromFile(unordered_map<int, vector<PCS>>& graph, unordered_map<int, pipe>& groupP, unordered_map<int, compressor_station>& groupCS, string str);

void OutputGraphToFile(const unordered_map<int, vector<PCS>>& graph, const unordered_map<int, pipe>& groupP, const unordered_map<int, compressor_station>& groupCS, string str);

void DeleteCSGraph(unordered_map<int, vector<PCS>>& graph, unordered_map<int, compressor_station>& groupCS);

unordered_map<int, bool> CountVertex(unordered_map<int, vector<PCS>>& graph);

void ShortPath(unordered_map<int, vector<PCS>>& graph, unordered_map<int, pipe>& pipe_group);