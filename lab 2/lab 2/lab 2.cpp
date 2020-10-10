// lab 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string.h>
#include <ctime>

using namespace std;

struct ListElem
{
	char* value;
	ListElem *next;
};

class List
{
	ListElem *pbeg, *pend;
public:
	List() { pend = pbeg = NULL; }
	~List() { clear(); }
	void push_front(char* val);
	char* pop_front();
	void clear();
	void push_back(char* val);
	ListElem * find_elem(char* keyval);
	//bool remove(char* keyval);
	//ListElem * find_el(char* keyval);
	//int find(char* keyval);
	friend ostream& operator<<(ostream &stream, List &t);
};

void List::push_front(char* val)
{
	ListElem *pnew = new ListElem;
	pnew->value = val; pnew->next = pbeg;
	pbeg = pnew; if (!pend) pend = pnew;
}

char* List::pop_front()
{
	if (!pbeg) return NULL;
	ListElem *ptr = pbeg;
	char* val = pbeg->value;
	pbeg = pbeg->next;
	if (!pbeg) pend = NULL;
	delete ptr;
	return val;
}

void List::clear()
{
	ListElem *ptr;
	while (pbeg != NULL)
	{
		ptr = pbeg; pbeg = pbeg->next;
		delete ptr;
	}
}

void List::push_back(char* val)
{	
	ListElem *pnew = new ListElem; 
	pnew->value = val; pnew->next = NULL;
	if (!pbeg) pbeg = pend = pnew;
	else { pend->next = pnew; pend = pnew; } 
}

//ListElem* List::find_elem(char* keyval, ListElem*& prev)
//{
//	ListElem *pcur = pbeg; prev = NULL;
//	while (pcur && pcur->value != keyval)
//	{
//		prev = pcur; pcur = pcur->next;
//	}
//	return pcur;
//}

ListElem* List::find_elem(char* keyval)
{
	ListElem *pcur = pbeg;
	for (; pcur; pcur = pcur->next)
		if (strcmp(pcur->value,keyval) == 0) break;
	return pcur;
}


//bool List::remove(char* keyval)
//{
//	ListElem *prem, *prev;
//	prem = find_elem(keyval, prev);
//	if (!prem) return false;
//	if (!prev) pbeg = pbeg->next;
//	else prev->next = prem->next;
//	if (prem == pend) pend = prev;
//	delete prem;
//	return true;
//}

//ListElem* List::find_el(char* keyval) {
//	ListElem *pcur = pbeg; 	for (; pcur; pcur = pcur->next)	
//		if (pcur->value == keyval) break;
//	return pcur;
//}

//int List::find(char* keyval)
//{
//	ListElem *ptr = find_el(keyval);
//	if (!ptr) return -1;
//	return 1;
//}

ostream& operator<<(ostream &stream, List &t)
{
	ListElem *ptr;
	ptr = t.pbeg;
	while (ptr != NULL)
	{
		stream << ptr->value << " "; ptr = ptr->next;
	}
	return stream;
}

class HashTable
{
private:
	int size;
	List* chain;
public:
HashTable(int n) 
	{ 
		size = n; chain = new List[size];
	}

int getHash(char* line)
{
	int hash = 0;
	for (int i = 0; i < strlen(line); i++) 
	{ 
		hash += (int)line[i];
		hash *= 31;
	}
	hash += (int)line[strlen(line)];
	hash = hash % size;
	return hash;
}

void addElem(char* val) 
{
	chain[getHash(val)].push_front(val);
}

void addElem2(char* val)
{
	if (chain[getHash(val)].find_elem(val) == NULL)
		chain[getHash(val)].push_front(val);
}

//void delElem(char* val)
//{
//	if (chain[getHash(val)].find(val) == 1) chain[getHash(val)].remove(val);
//	else cout << "Element not found";
//}

void addRnd(int length)
{
	char* s = new char[length];
	for (int i = 0; i < length; i++) s[i] = 'a' + rand() % 25;
	s[length] = '\0'; addElem(s);
}

friend ostream& operator<<(ostream &stream, HashTable &b)
{ 		
	for (int i = 0; i < b.size; i++)
	{
		stream << b.chain[i] << endl;
	} 		
	return stream;
} 
};

int main()
{
	srand(time(0));
	/*int n, q;
	cout << "Vvedite nachalnoe kol-vo strok" << endl; cin >> n;
	cout << "Vvedite q" << endl; cin >> q;
	HashTable ht(q); for (int i = 0; i < n; i++) ht.addRnd(4);
	cout << ht;*/

	// check unique
	/*HashTable test(10);
	test.addElem2("qwe"); test.addElem2("asd"); test.addElem2("qwe"); test.addElem2("asd"); test.addElem2("zxc");
	cout << test;*/
	return 0;
}