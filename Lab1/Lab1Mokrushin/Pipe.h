#pragma once
#include<iostream>
#include<fstream>
#include "unordered_map"
class pipe
{
	int id;
	static int MaxID;
public:
	int diameter;
	float length;
	bool work;
	int GetId();
	pipe();

	friend std::ostream& operator << (std::ostream& out, const pipe& pipe_i);
	friend std::istream& operator >> (std::istream& in, pipe& pipe_i);
	friend std::ofstream& operator << (std::ofstream& OutFile, const pipe& pipe_i);
	friend std::ifstream& operator >> (std::ifstream& InFile, pipe& pipe_i);
};

