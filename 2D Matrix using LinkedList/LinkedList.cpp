//2D MATRIX WITH LINKEDLIST
#include <iostream>
#include <stdexcept>
#define COL 3
#define ROW 3
using namespace std;

template<class T>
class LinkedList {
public:
	T data;
	LinkedList *Next;
	LinkedList *Prev;
	LinkedList *NextRow;
	LinkedList *PrevRow;
public:

	LinkedList(T data) {
		this->data = data;
		Next = nullptr;
		Prev = nullptr;
		NextRow = nullptr;
		PrevRow = nullptr;
	}
	void add(int data) {
		if (Next == nullptr){
			if ((Rlength(true).second+ Rlength(false).second)<COL+1){
				Next = new LinkedList(data);
				Next->Prev = this;
				return;
			}
			if (NextRow){
				NextRow->add(data);
				return;
			}
			else if((length(true).first+length(false).first)<ROW+1){
					NextRow = new LinkedList(data);
					NextRow->PrevRow = this;
					return;
			}
		}
		Next->add(data);
	}
	//all length
	pair<int, int> length(bool isNext){
		LinkedList *iter = this;
		pair<int, int> size = { 0,0 };
		while (iter) {
			size.second++;
			if ((isNext ? iter->Next : iter->Prev)==nullptr) {
				
				if ((isNext ? iter->NextRow : iter->PrevRow)) {
					iter = (isNext ? iter->NextRow : iter->PrevRow);
					size.first++;
					continue;
				}
			}
			iter = (isNext ? iter->Next : iter->Prev);
		}
		return size;
	}
	// ROW'column length
	pair<int, int> Rlength(bool isNext) {
		LinkedList *iter = this;
		pair<int, int> size = { 0,0 };
		while (iter) {
			size.second++;
			iter = (isNext ? iter->Next : iter->Prev);
		}
		return size;
	}
};
int main() {
	LinkedList<int> *Root = new LinkedList<int>(0);
	Root->add(1);
	Root->add(2);
	Root->add(3);
	Root->add(4);
	Root->add(5);
	Root->add(6);
	Root->add(7);
	Root->add(8);
	pair<int, int> a = Root->length(true);
	cout << a.first << " " << a.second;
}