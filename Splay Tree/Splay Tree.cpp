//Splay Tree
#include <iostream>

struct Node{
	int key;
	Node *left,*right;
	
	Node(int key_):key(key_){
		left=right=nullptr;
	}
};
//Tree Class
class Tree{
public:
	static Node *add(Node *root,int key){
		if(root==nullptr)	
			return new Node(key);			
		if(root->key > key)
			root->left=add(root->left,key);
		else if(root->key < key)
			root->right=add(root->right,key);
		else
			return root;
	}
	static bool search(Node *&root,int key_){
		root=splay(root,key_);
		return (root->key==key_ ? true : false);
	}
private:
	static Node *rightRotate(Node *root){
		Node *temp=root->left;
		root->left=temp->right;
		temp->right=root;
		
		return temp;
	}
	static Node *leftRotate(Node *root)
	{
		Node *temp=root->right;
		root->right=temp->left;
		temp->left=root;
		
		return temp;
	}
	//Splay 
	static Node *splay(Node *root,int key)
	{
		if(root==nullptr || root->key==key)
			return root;
		
		if(root->key>key)
		{
			if(root->left==nullptr)
				return root;
			
			//Zig Zig (left-left)
			if(root->left->key>key)
			{
				root->left->left=splay(root->left->left,key);
				
				root=rightRotate(root);
			}
			//Zig Zag(left-right)
			else if(root->left->key<key)
			{
				root->left->right=splay(root->left->right,key);
				
				if(root->left->right!=nullptr)
					root->left=leftRotate(root->left);
			}
			return (root->left==nullptr) ? root : rightRotate(root);
		}
		else if(root->key<key)
		{
			if(root->right==nullptr)
				return root;
			//Zag-Zag (right-right)
			if(root->right->key<key)
			{
				root->right->right=splay(root->right->right,key);
				
				root=leftRotate(root);
			}
			//Zag-Zig(Right Left)
			else if(root->right->key>key)
			{
				root->right->left=splay(root->right->left,key);
				
				if(root->right->left!=nullptr)
					root->right=rightRotate(root->right);
			}
			return (root->right==nullptr) ? root : leftRotate(root);
		}
	}
};

//Test
int main(){
	Node *root=nullptr;
	
	root=Tree::add(root,100);
	root=Tree::add(root,200);
	root=Tree::add(root,50);
	root=Tree::add(root,40);
	
	std::cout<<Tree::search(root,50)<<std::endl;
	
	std::cout<<root->key;

}