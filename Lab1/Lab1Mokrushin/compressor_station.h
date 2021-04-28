#pragma once
#include<string>
#include<iostream>
#include<fstream>
class compressor_station
{
	int id;
	static int MaxID;
	float efficiency;
public:
	std::string name;
	int manufactory;
	int manufactory_w;
	int GetId();
	compressor_station();
	static unsigned int GetMaxID();

	friend std::ostream& operator << (std::ostream& out, const compressor_station& CS_i);
	friend std::istream& operator >> (std::istream& in, compressor_station& CS_i);
	friend std::ofstream& operator << (std::ofstream& OutFile, const compressor_station& CS_i);
	friend std::ifstream& operator >> (std::ifstream& InFile, compressor_station& CS_i);
};

