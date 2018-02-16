#ifndef TREE_H
#define TREE_H
#include <cstdlib>
using namespace std;
class Llist{
public:
	Llist *Next;
	int Data;
	Llist(int x):Data(x){
		Next=NULL;
	}
};
class Tree{
	int Data;
	Tree *Left;
	Tree *Right;
	Tree *Parent;
public:
	Tree(int x){
		Left=NULL;
		Right=NULL;
		Parent=NULL;
		Data=x;
	}
	bool Add(int);
	bool Delete(int);
	void Show();
	int Height();
	bool Find(int);
	int Min();
	int Max();	
	void ToList(Llist*);
};
Llist *LAdd(Llist*,int);
void LShow(const Llist*);
#endif
