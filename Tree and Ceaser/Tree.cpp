#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include "Tree.h"
using namespace std;
void Tree::Add(string item, int key) {
	if (Key>key) {
		if (Left)
			Left->Add(item, key);
		Left = new Tree(item, key);
		Left->Parent = this;
		return;
	}
	else if (Key<key) {
		if (Right)
			Right->Add(item, key);
		Right = new Tree(item, key);
		Right->Parent = this;
		return;
	}
}
void Tree::Remove(int key){
	if (Key>key) {
		if (Left)
			Left->Remove(key);
		else
			return;
	}
	else if (Key<key) {
		if (Right)
			Right->Remove(key);
		else
			return;
	}
	if (Key == key) {
		if (Parent == NULL) {
			if (Left) {
				Tree *temp = Left->Max();
				Value = temp->Value;
				Key = temp->Key;
				Box=temp->Box;
				return Left->Remove(temp->Key);
			}
			else if (Right) {
				Tree *temp = Right->Min();
				Value = temp->Value;
				Key = temp->Key;
				Box=temp->Box;
				return Right->Remove(temp->Key);
			}
			else {
				delete this;
				return;
			}
		}
		if (Left == NULL && Right == NULL) {
			if (Parent->Left == this)
				Parent->Left = NULL;
			else
				Parent->Right = NULL;
			delete this;
			return;
		}
		else if (Left != NULL && Right != NULL) {
			Tree *temp = Left->Max();
			Key = temp->Key;
			Value = temp->Value;
			Box.clear();
			Box[Key] = Value;
			return Left->Remove(temp->Key);
		}
		else if (Left) {
			if (Parent->Left == this)
				Parent->Left = Left;
			else
				Parent->Right->Left;
			Right->Parent = Parent;
			delete this;
		}
		else {
			if (Parent->Left == this)
				Parent->Left = Right;
			else
				Parent->Right = Right;
			Right->Parent = Parent;
			delete this;
		}
	}
	else
		return;
}
Tree *Tree::Find(int key) {
	if (key == Key)
		return this;
	if (Key>key && Left != NULL)
		return Left->Find(key);
	else if (key>Key && Right != NULL)
		return Right->Find(key);
	else
		return NULL;
}
Tree *Tree::Min() {
	if (Left == NULL)
		return this;
	return Left->Min();
}
Tree *Tree::Max() {
	if (Right == NULL)
		return this;
	return Right->Max();
}
