#include <iostream>
#include <ctime>
#include "Tree.h"
using namespace std;
int main(){
	Tree *Root=new Tree(15);
	Llist *LRoot=new Llist(1);
	Root->Add(10);
	Root->Add(25);
	Root->Add(5);
	Root->Add(20);
	Root->Add(7);
	Root->Add(52);
	Root->Show(); 
	cout<<endl;
	system("pause");
	Root->ToList(LRoot);
	LShow(LRoot);
}
