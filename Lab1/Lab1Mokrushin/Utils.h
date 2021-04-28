#pragma once
#include<iostream>

using namespace std;
template <typename T>

T GetCorrectNumber(T left, T right)
{
	T x;
	while (((cin >> x)).fail() || x<left || x>right)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "ќшибка при вводе!" << endl << "¬ведите команду: ";
	}
	return x;
}