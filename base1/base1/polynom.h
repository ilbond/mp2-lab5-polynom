#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;

class monom
{
public:
	monom() {
		c = 0; lay = 0;
	}
	monom(double a, long int b) {
		c = a; lay = b;
	}
	double c;
	long int lay = 0;
	bool operator<=(monom &a)
	{
		return lay <= a.lay;
	}
	bool operator<(monom &a)
	{
		return lay < a.lay;
	}
	bool operator>=(monom &a)
	{
		return lay >= a.lay;
	}
	bool operator>(monom &a)
	{
		return lay > a.lay;
	}
	bool compare(const monom &a) {
		return (lay >= a.lay);
	};
};

class polynom
{
	int max = 10;
	class Node
	{
	public:
		Node* pNext;
		monom data;
		Node() {};
		Node(monom data, Node *pp) {
			this->data = data;
			this->pNext = pp;
		}
		Node(Node *pp) {
			this->pNext = pp;
		}
		Node(monom data) { this->data = data; }
	};
	Node * pFirst;
	string poly;
public:
	polynom();
	polynom(const polynom &a);
	polynom &operator=(const polynom &a);
	polynom operator+(const polynom &a);
	polynom &operator+=(const polynom &a);
	polynom operator-(const polynom &a);
	polynom operator*(const polynom &a);
	polynom operator*(const double &a);
	polynom derative(const char &a);
	polynom integration(const char &a);
	void DeleteSpace();
	void InsertSpace();
	void CheckPolynom();
	void InputPolynom(string &a);
	void Record();
	void Translate2List(vector<monom> p);
	vector<monom> Translate2Vector();
	void Cast();
	~polynom();
};

