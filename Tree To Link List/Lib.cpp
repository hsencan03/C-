#include "Tree.h"
#include <iostream>
#include <cstdlib>
#include <new>
Llist *LAdd(Llist*Root,int data){
	if(Root==NULL){
		Root=new Llist(data);
		return Root;
	}
	Llist *iter=Root;
	while(iter->Next!=NULL)
		iter=iter->Next;
	iter->Next=new Llist(data);
	return Root;
}
void LShow(const Llist*Root){
	if(Root==NULL)
		return;
	cout<<Root->Data<<" ";
	return LShow(Root->Next);
}
bool Tree::Add(int data){
	try{
		if(Data>data){
			if(Left)
				return Left->Add(data);
			Left=new Tree(data);
			Left->Parent=this;
			return true;
		}
		else if(Data<data){
			if(Right)
				return Right->Add(data);
			Right=new Tree(data);
			Right->Parent=this;
			return true;
		}
	}
	catch(bad_alloc &e){
		cout<<e.what();
		return false;
	}
}
bool Tree::Delete(int data){
	if(Data==data){
		if(Left){
			Data=Left->Max();
			return Left->Delete(Left->Max());
		}
		else if(Right){
			Data=Right->Min();
			return Right->Delete(Right->Min());
		}
		else{
			if(Parent->Right==this){
				Parent->Right=NULL;
				delete this;
				return true;
			}
			else if(Parent->Left==this){
				Parent->Left=NULL;
				delete this;
				return true;
			}
			else{
				delete this;
				return true;
			}
		}
	}
	else if(Data>data){
		if(Left)
			return Left->Delete(data);
		return false;
	}
	else if(Data<data){
		if(Right)
			return Right->Delete(data);
		return false;
	}
}
void Tree::Show(){
	if(this==NULL)
		return;
	Left->Show();
	cout<<Data<<" ";
	Right->Show();
}
int Tree::Height(){
	if(this==NULL)
		return 0;
	else{
		int LHeight=Left->Height();
		int RHeight=Right->Height();
		if(LHeight>RHeight)
			return (LHeight+1);
		return (RHeight+1);
	}
}
bool Tree::Find(int data){
	if(this==NULL)
		return false;
	else if(Data==data)
		return true;
	else if(Data>data)
		return Left->Find(data);
	else if(Data<data)
		return Right->Find(data);
}
int Tree::Max(){
	if(Right==NULL)
		return this->Data;
	return Right->Max();
}
int Tree::Min(){
	if(Left==NULL)
		return this->Data;
	return Left->Min();
}
void Tree::ToList(Llist*Root){
	if(this->Left)
		this->Left->ToList(Root);
	Root=LAdd(Root,this->Data);
	if(this->Right)
		this->Right->ToList(Root);
}
