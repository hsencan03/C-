#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <iostream>
class Piece;

template<typename T,typename std::enable_if<(std::is_same<Piece*,T>::value) || (std::is_base_of<Piece,T>::value)>::type* =nullptr>
class LinkedList{
private:
	struct Node{
		T data;
		Node *next,*prev;
		//Node's constructer
		Node(T data){
			this->data=data;
			next=nullptr;
			prev=nullptr;
		}
		friend std::ostream& operator<<(std::ostream& os,const Node* node){
			if(node==nullptr)
				os<<-1;
			else
				os<<node->data;
		}
	};
	Node *Root;
public:
	LinkedList():Root(nullptr){}
	LinkedList(T data){
		Root=new Node(data);
	}
	~LinkedList(){
		delete Root;
	}
	void add(T data){
		if(Root==nullptr){
			Root=new Node(data);
		}
		Node *iter=Root;
		while(iter->next!=nullptr)
			iter=iter->next;
		iter->next=new Node(data);
		iter->next->prev=iter;
		return;
	}
	bool remove(Node *obj){
		if(Root==obj){
			Root->data=nullptr;
			return true;
		}
		Node *iter=Root;
		while(iter!=obj){
			iter=iter->next;
			if(iter==nullptr)
				return false;
		}
		if(iter->next!=nullptr){
			iter->prev->next=iter->next;
			iter->next->prev=iter->prev;
		}
		else
			iter->prev->next=nullptr;
			
		delete iter;
		return true;
	}
	bool remove(const T &data){
		if(Root->data==data){
			Root->data=nullptr;
			return true;
		}
		Node *iter=Root;
		while(iter->data!=data){
			iter=iter->next;
			if(iter==nullptr)
				return false;
		}
		if(iter->next!=nullptr){
			iter->prev->next=iter->next;
			iter->next->prev=iter->prev;
		}
		else
			iter->prev->next=nullptr;
			
		delete iter;
		return true;		
	}
	Node *at(int index){
		Node *iter=Root;
		for(int i=0;iter!=nullptr && i<index;i++)
			iter=iter->next;
		return iter;
	}
	int size(){
		Node *iter=Root;
		int count=1;
		while(iter->next){
			count++;
			iter=iter->next;
		}
		return count;
	}
	bool contains(std::string name,bool color){
		for (int i = 0; i<size(); i++) {
			if (at(i).name == name && at(i).color == color)
				return true;
		}
		return false;
	}
};
#endif
