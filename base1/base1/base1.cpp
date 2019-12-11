#include "pch.h"
#include "polynom.h"
#include <iostream>
using namespace std;
int main()
{
	string a = "2x2y2z2";
	string b = "5x2y3z2-7x2y2z2";
	polynom m,k;
	k.InputPolynom(b);
	m.InputPolynom(a);
	m.Record(); 
	k.Record();
	m.Cast(); k.Cast();
	polynom volk;
	volk = m - k;
	volk = m * k;
	volk = k * 2;
}
