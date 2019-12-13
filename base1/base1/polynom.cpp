#include "pch.h"
#include "polynom.h"
#include <sstream>
#include <vector>
polynom::polynom()
{
	monom a(0, -1);
	poly = { };
	pFirst = new Node(a);
	pFirst->pNext = pFirst;
}

polynom::polynom(string &a) {
	poly=a;
	Record();
	Cast();
	Translate2String();
}
polynom::polynom(const polynom &a) {
	poly = a.poly;
	monom b(0,-1);
	pFirst = new Node(b);
	pFirst->pNext = pFirst;
	Node *p = a.pFirst->pNext;
	Node *pp = pFirst->pNext;
	while (p != a.pFirst)
	{
		pp->pNext = new Node({ p->data.c,p->data.lay }, pFirst);
		pp = pp->pNext;
		p = p->pNext;
	}
}

void polynom::DeleteSpace() {
	for (int i = 0; i < poly.size(); i++) {
		if (poly[i] == ' ') {
			poly.erase(i, 1);
		}
	}
}

void polynom::InsertSpace() {
	string word;
	string str;
	string res;
	for (int i = 0; i < poly.size(); i++)
	{
			str = poly[i];
			if ((poly[i] == 43) || (poly[i] == 45))
			{
				res += word;
				word.clear();
				res += ' ' + str;
			}
			else
			{
				word += str;
			}
		}
	res += word;
	poly = res;
}
void polynom::InputPolynom(const string &a) {
	poly = a;
}

void polynom::CheckPolynom() {
	DeleteSpace();
	InsertSpace();
	string Word;// PrevWord;
	int j = 0, s = 0, f = 0;
	for (stringstream is(poly); is >> Word;) {
		for (int i = 0; i < Word.length(); i++) {
			if (((Word[i] < 43) || (Word[i] > 57)) && ((Word[i] < 120) || (Word[i] > 122)) || (Word[i] == 42) || (Word[i] == 44) || (Word[i] == 47)) {
				throw 1;
			}
			if ((j > 3) || (s > 1))
				throw 1;
			if ((Word[i] >= 120) && (Word[i] <= 122)) {
				j = 0; f = 1;
			}
			if (Word[i] == 46)
				s++;
			if (f == 1) {
			    if ((Word[i] >= 48) && (Word[i] <= 57)) {
					j++;
				}
			}
		}
	    f = 0; s = 0; j = 0;
	}
}

bool comp(monom a, monom b)
{
	return a.compare(b);
}

void polynom::Record() {
	CheckPolynom();
	//InsertSpace();
	vector<monom> p;
	string Word;
	int f = 0;
	vector<int> v;
	long int c; double b;
	for (stringstream is(poly); is >> Word;) {
		string str[4] = {"0","0","0","0"};
		bool r[4] = { false, false, false, false };
		for (int i = 0; i < Word.length(); i++) {
			
			if (Word[i] == 120)
			{
				f = 1;
				r[1] = true;
			}
			if (Word[i] == 121)
			{
				f = 2;
				r[2] = true;
			}
			if (Word[i] == 122)
			{
				f = 3;
				r[3] = true;
			}
				
			if ((Word[i] >= 48) && (Word[i] <= 57)||(Word[i]==46)) {
					str[f] += Word[i];
					v.push_back(f);
			}
		}
		for (int i = 0; i < 4; ++i)
		{
			if (r[i] && str[i] == "0")
				str[i] += "1";
		}
		c = pow(max, 2)*atoi(str[1].c_str()) + max * atoi(str[2].c_str()) + atoi(str[3].c_str());
		if (Word[0] == '-')
			str[0] = '-' + str[0];

		if (str[0] == "0")
		{
			b = 1;
		}
		else if (str[0] == "-0")
		{
			b = -1;
		}
		else {
			stringstream s(str[0]);
			s >> b;
		}
		monom a(b, c);
		p.push_back(a);
		f = 0;
	}
	sort(p.begin(), p.end());
	Translate2List(p);
}

void polynom::Translate2List(vector<monom> p) {
	monom a(0, -1); 
	pFirst = new Node(a);
	pFirst->pNext = pFirst;
	Node *tmp = pFirst;
	Node *pp=new Node(a);
	for (int i = 0; p.size(); i++) {
		pp = new Node(a,pFirst);
		pp->data = p.back();
		tmp->pNext = pp;
		p.pop_back();
		tmp = tmp->pNext;
	}
}

vector<monom> polynom::Translate2Vector() {
	Node *tmp = pFirst->pNext;
	Node *pp;
	vector<monom> p;
	while (tmp!=pFirst) {
		p.push_back(tmp->data);
		pp = tmp;
		tmp = tmp->pNext;
		delete pp;
	}
 	delete pFirst;
	return p;
}

void polynom::Cast() {
	Node *tmp = pFirst->pNext;
	Node *pp = pFirst;
	while (pp->pNext != pFirst) {
		if (tmp->data.lay == pp->data.lay)
		{
			pp->data.c += tmp->data.c;
			pp->pNext = tmp->pNext;
			delete tmp;
			tmp = pp->pNext;
		}
		else
		{
			pp = pp->pNext;
			tmp = pp->pNext;
		}
	}
	pp = pFirst->pNext;
	Node *pr = pFirst;
	while (pp != pFirst)
	{
		if (pp->data.c == 0)
		{
			pr->pNext = pp->pNext;
			delete pp;
			pp = pr->pNext;
		}
		else
		{
			pp = pp->pNext;
			pr = pr->pNext;
		}
	}
}

polynom& polynom::operator=(const polynom &a) {
	if (a.pFirst == pFirst)
		return *this;
	poly = a.poly;
	Node *p = pFirst->pNext;
	while (p != pFirst) {
		pFirst->pNext = p->pNext;
		delete p;
		p = pFirst->pNext;
	}
	p = a.pFirst->pNext;
	Node *pp = pFirst;
	while (p != a.pFirst)
	{
		pp->pNext = new Node(p->data,p->pNext);
		pp = pp->pNext;
		p = p->pNext;
	}
	pp->pNext = pFirst;
	Translate2String();
	return *this;
}
polynom polynom::operator+(const polynom &a) {
	polynom b(*this);
	polynom f(a);
	monom m(0, -1);
	Node *tmp = b.pFirst->pNext;
	Node *tmp2 = b.pFirst;
	while (tmp != b.pFirst)
	{
		tmp = tmp->pNext;
		tmp2 = tmp2->pNext;
	}
	tmp2->pNext = f.pFirst->pNext;
	tmp2 = tmp2->pNext;
	while (tmp2->pNext != f.pFirst)
	{
		tmp2 = tmp2->pNext;
	}
	tmp2->pNext = b.pFirst;
	delete f.pFirst;
	f.pFirst = new Node(m);
	f.pFirst->pNext = f.pFirst;
	vector<monom> v = b.Translate2Vector();
	sort(v.begin(), v.end());
	b.Translate2List(v);
	b.Cast();
	b.Translate2String();
	return b;
}

polynom polynom::operator-(const polynom &a) {
	polynom b(*this);
	polynom f(a);
	monom m(0, -1);
	Node *tmp = b.pFirst->pNext;
	Node *tmp2 = b.pFirst;
	while (tmp != b.pFirst)
	{
		tmp = tmp->pNext;
		tmp2 = tmp2->pNext;
	}
	tmp2->pNext = f.pFirst->pNext;
	tmp2 = tmp2->pNext;
	while (tmp2->pNext != f.pFirst)
	{
		tmp2->data.c *= (-1);
		tmp2 = tmp2->pNext;
	}
	tmp2->data.c *= (-1);
	tmp2->pNext = b.pFirst;
	delete f.pFirst;
	f.pFirst = new Node(m);
	f.pFirst->pNext = f.pFirst;
	vector<monom> v = b.Translate2Vector();
	sort(v.begin(), v.end());
	b.Translate2List(v);
	b.Cast();
	b.Translate2String();
	return b;
}

polynom& polynom::operator+=(const polynom &a) {
	polynom f(a);
	monom m(0, -1);
	Node *tmp = pFirst->pNext;
	Node *tmp2 = pFirst;
	while (tmp != pFirst)
	{
		tmp = tmp->pNext;
		tmp2 = tmp2->pNext;
	}
	tmp2->pNext = f.pFirst->pNext;
	tmp2 = tmp2->pNext;
	while (tmp2->pNext != f.pFirst)
	{
		tmp2 = tmp2->pNext;
	}
	tmp2->pNext = pFirst;
	delete f.pFirst;
	f.pFirst = new Node(m);
	f.pFirst->pNext = f.pFirst;
	vector<monom> v = Translate2Vector();
	sort(v.begin(), v.end());
	Translate2List(v);
	Cast();
	Translate2String();
	return *this;
}

polynom polynom::operator*(const double &a) {
	polynom b(*this);
	Node *p = b.pFirst->pNext;
	while (p != b.pFirst) {
		p->data.c *= a;
		p = p->pNext;
	}
	b.Translate2String();
	return b;
}

polynom polynom::operator*(const polynom &a) {
	polynom b;
	polynom f(a);
	Node *p = pFirst->pNext;
	Node *pp = f.pFirst->pNext;
	Node *tmp = b.pFirst;
	while (p != pFirst) {
		while (pp != f.pFirst)
		{
			tmp->pNext = new Node({ p->data.c * pp->data.c, p->data.lay + pp->data.lay
		}, tmp->pNext);
			tmp = tmp->pNext;
			pp = pp->pNext;
		}
		p = p->pNext;
		pp = pp->pNext;
	}
	vector<monom> v = b.Translate2Vector();
	sort(v.begin(), v.end());
	b.Translate2List(v);
	b.Cast();
	b.Translate2String();
	return b;
}

polynom polynom::derative(const char &a) {
	polynom b(*this);
	int tmp = 120,i=0;
	Node *p = b.pFirst->pNext;
	Node *pp = b.pFirst;
	while (p != b.pFirst) {
		long int q = p->data.lay;
		if (a == 122) {
			int q1 = pow(max, 2);
			q = q  % max;
		}
		if (a == 121) {
			int q1 = pow(max, 2);
			q = q / max % max;
		}
		if (a==120){
			int q1 = pow(max, 2);
			q = q / q1;
			tmp++;
		}
		int w = q;
		p->data.c *= w;
		p->data.lay -= pow(max, 122 - a);
		if (q == 0) {
			pp->pNext = p->pNext;
			delete p;
			p = pp->pNext;
		}
		else
		    p = p->pNext;
		pp = pp->pNext;
	}
	b.Translate2String();
	return b;
}

polynom polynom::integration(const char &a) {
	polynom b(*this);
	int tmp = 120, i = 1;
	Node *p = b.pFirst->pNext;
	while (a >= tmp) {
		tmp++;
	}
	while (p != b.pFirst) {
		long int q = p->data.lay;
		if (a == 122) {
			int q1 = pow(max, 2);
			q = q % max;
		}
		if (a == 121) {
			int q1 = pow(max, 2);
			q = q / max % max;
		}
		if (a == 120) {
			int q1 = pow(max, 2);
			q = q / q1;
			tmp++;
		}
		int w = q+1;
		p->data.c *= 1/ static_cast<double>(w);;
		p->data.lay += pow(max, 122 - a);
		p = p->pNext;
	}
	b.Translate2String();
	return b;
}

void polynom::Translate2String() {
	Node *p = pFirst->pNext;
	string str;
	while (p != pFirst) {
		string tmp;
		if (p->data.c > 0) {
			str += "+";
		}
		tmp = to_string(p->data.c);
		str += tmp;
		if (p->data.lay / static_cast<int>(pow(max, 2)) != 0) {
			str += "x";
			if (p->data.lay / static_cast<int>(pow(max, 2)) > 1) {
				tmp = to_string(p->data.lay / static_cast<int>(pow(max, 2)));
				str += tmp;
			}
		}
		if (((p->data.lay / static_cast<int>(pow(max, 1)))% static_cast<int>(pow(max, 1))) != 0) {
			str += "y";
			if (((p->data.lay / static_cast<int>(pow(max, 1))) % static_cast<int>(pow(max, 1))) > 1) {
				tmp = to_string((p->data.lay / static_cast<int>(pow(max, 1))) % static_cast<int>(pow(max, 1)));
				str += tmp;
			}
		}
		if ((p->data.lay % max) != 0) {
			str += "z";
			if ((p->data.lay % max) > 1) {
				tmp = to_string(p->data.lay % max);
				str += tmp;
			}
		}
		p = p->pNext;
	}
	poly = str;
}

double polynom::Calculate(const double a[]) {
	double res=0;
	Node *p = pFirst->pNext;
	while (p != pFirst) {
		double tmp=0;
		int px = p->data.lay / static_cast<int>(pow(max, 2));
		int py = (p->data.lay / static_cast<int>(pow(max, 1))) % static_cast<int>(pow(max, 1));
		int pz = p->data.lay % max;
		tmp += p->data.c*pow(a[0],px)*pow(a[1],py)*pow(a[2],pz);
		res += tmp;
		p = p->pNext;
	}
	return res;
}
polynom::~polynom()
{
	Node *p = pFirst->pNext;
	while (p != pFirst)
	{
		pFirst->pNext = p->pNext;
		delete p;
		p = pFirst->pNext;
	}
	delete pFirst;
}
