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
void polynom::InputPolynom(string &a) {
	poly = a;
}

void polynom::CheckPolynom() {
	DeleteSpace();
	char Word, PrevWord;
	int i = 0,s=0;
	for (stringstream is(poly); is >> Word;) {
		if (((Word < 43) || (Word > 57)) && ((Word < 120) || (Word > 122)) && (Word==42) && (Word == 44) && (Word == 47)) {
			throw 1;
		}
		if ((Word >= 120) || (Word <= 122)) {
			i++;
			if ((PrevWord < 48) || (PrevWord > 57))
				throw 1; 
		}
		if (Word == 46)
			s++;
		if ((i > 6)||(s>1))
			throw 1;
		if ((Word == 43) || (Word == 45)) {
			i = 0;
			s = 0;
			if ((PrevWord < 48) || (PrevWord > 57))
				throw 1;
		}
		PrevWord = Word;
	}
}

bool comp(monom a, monom b)
{
	return a.compare(b);
}

void polynom::Record() {
	//CheckPolynom();
	InsertSpace();
	vector<monom> p;
	string Word;
	int f=0;
	long int c; double b;
	for (stringstream is(poly); is >> Word;) {
		string strx, stry, strz, str;
		for (int i = 0; i < Word.length(); i++) {
			
			if (Word[i] == 120)
				f = 3;
			if (Word[i] == 121)
				f = 2;
			if (Word[i] == 122)
				f = 1;
			if ((Word[i] >= 48) && (Word[i] <= 57)||(Word[i]==46)) {
				if (f == 0) {
					str += Word[i];
				}
				if (f == 3) {
					strx += Word[i];
				}
				if (f == 2) {
					stry += Word[i];
				}
				if (f == 1) {
					strz += Word[i];
				}
			}
		}
		c = pow(max, 2)*atoi(strx.c_str()) + max * atoi(stry.c_str()) + atoi(strz.c_str());
		if (Word[0] == '-')
			str = '-'+str;
		stringstream s(str);
		s >> b;
		monom a(b, c);
		p.push_back(a);
		f = 0;
	}
	sort(p.begin(), p.end());
	Translate2List(p);
}

void polynom::Translate2List(vector<monom> p) {
	Node *tmp = pFirst;
	monom a(0, -1);
	for (int i = 0; p.size(); i++) {
		tmp->pNext = new Node(a,pFirst);
		tmp->data = p.back();
		p.pop_back();
		tmp = tmp->pNext;
	}
	pFirst = tmp;
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
	Node *pp;
	while (tmp != pFirst) {
		pp = tmp;
		tmp = tmp->pNext;
		if (pp->data.lay == tmp->data.lay) {
			pp->data.c += tmp->data.c;
			pp->pNext = tmp->pNext;
		}
	}
}

polynom& polynom::operator=(const polynom &a) {
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
	return *this;
}
polynom polynom::operator+(const polynom &a) {
	polynom b(*this);
	polynom f(a);
	monom m(0, -1);
	Node *tmp = b.pFirst->pNext;
	Node *pp=b.pFirst;
	while (tmp != b.pFirst) {
		pp = tmp;
		tmp = tmp->pNext;
	}
	pp->pNext = f.pFirst->pNext;
	tmp= f.pFirst->pNext;
	while (tmp != f.pFirst) {
		pp = tmp;
		tmp = tmp->pNext;
	}
	pp->pNext = b.pFirst;
	vector<monom> v = b.Translate2Vector();
	sort(v.begin(), v.end());
	b.Translate2List(v);
	b.Cast();
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
		tmp2 = tmp2->pNext;
	}
	tmp2->pNext = b.pFirst;
	/*Node *tmp = b.pFirst->pNext;
	Node *pp = b.pFirst;
	while (tmp != b.pFirst) {
		pp = tmp;
		tmp = tmp->pNext;
	}
	pp->pNext = f.pFirst->pNext;
	tmp = f.pFirst->pNext;
	while (tmp != f.pFirst) {
		tmp->data.c *= (-1);
		pp = tmp;
		tmp = tmp->pNext;
	}
	pp->pNext = b.pFirst;*/
	delete f.pFirst;
	f.pFirst = new Node(m);
	f.pFirst->pNext = f.pFirst;
	//vector<monom> v = b.Translate2Vector();
	//sort(v.begin(), v.end());
	//b.Translate2List(v);
	//b.Cast();
	return b;
}

polynom& polynom::operator+=(const polynom &a) {
	polynom b;
	return b;
}

polynom polynom::operator*(const double &a) {
	polynom b(*this);
	Node *p = b.pFirst->pNext;
	while (p != b.pFirst) {
		p->data.c *= a;
		p = p->pNext;
	}
	return b;
}

polynom polynom::operator*(const polynom &a) {
	polynom b;
	polynom f(a);
	//monom m(0, -1);
	Node *p = pFirst->pNext;
	Node *pp = f.pFirst->pNext;
	//Node *tmp = new Node(m, pFirst);
	Node *tmp = b.pFirst;
	while (p != pFirst) {
		while (pp != f.pFirst)
		{
			//tmp->data.c = p->data.c * pp->data.c;
			//tmp->data.lay = p->data.lay + pp->data.lay;
		
			tmp->pNext = new Node({ p->data.c * pp->data.c, p->data.lay + pp->data.lay
		}, tmp->pNext);
			tmp = tmp->pNext;
			pp = pp->pNext;
		}
	  //  pp = a.pFirst->pNext;
		p = p->pNext;
		//tmp = tmp->pNext;
	}
	//b.pFirst = tmp;
	return b;
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
