#ifndef Tree_H
#define Tree_H
#include <string>
#include <map>
#include "Ceaser.h"
using namespace std;
class Tree {
public:
	Tree * Left;
	Tree *Right;
	Tree *Parent;
	int Key;
	string Value;

	map<int, string>Box;
	Tree(string data, int key) :Value(data), Key(key) {
		Left = Right = NULL;
		Box[Key] =Ceaser::Encrypt(data,15);
		Parent = NULL;
	}
	void Add(string, int);
	void Remove(int);
	Tree *Find(int);
	Tree *Max();
	Tree *Min();

};
#endif
