#include <iostream>
#include <stack>
#include <queue>

class BST
{
public:
	struct Print;
	struct Node;

	BST(int value)
	{
		root = new Node({ value,nullptr,nullptr });
		prnt = new Print(this);
	}
	~BST()
	{
		if (root)
			delete root;
		if (prnt)
			delete prnt;
	}
	
	bool add(int value)
	{
		Node* temp = root;

		//where we add ?
		int isLeft{ -1 };

		while (true)
		{
			if (temp->data > value)
			{
				if (!temp->left)
				{
					isLeft = 1;
					break;
				}
				temp = temp->left;
			}
			else if (temp->data < value)
			{
				if (!temp->right)
				{
					isLeft = 0;
					break;
				}
				temp = temp->right;
			}
			else
				return false;
		}
		if (isLeft != -1)
		{
			if (isLeft == 1)
				temp->left = new Node({ value,nullptr,nullptr });
			else
				temp->right = new Node({ value,nullptr,nullptr });

			return true;
		}
	}

	bool remove(int value)
	{
		if (!root)
			return false;

		std::queue<Node*> qNode;
		qNode.push(root);

		while (!qNode.empty())
		{
			Node* temp = qNode.front();
			qNode.pop();

			if (!temp->left)
				qNode.push(temp->left);
			if (!temp->right)
				qNode.push(temp->right);

			delete temp;
			return true;
		}
	}

	bool find(int value)
	{
		Node* temp = root;

		if (!temp)
			return false;

		while (temp)
		{
			if (temp->data > value)
			{
				if (!temp->left)
					return false;

				temp = temp->left;
			}
			else if (temp->data < value)
			{
				if (!temp->right)
					return false;

				temp = temp->right;
			}
			else
				return true;
		}

		return false;
	}

	Print& print()
	{
		return *prnt;
	}


private:
	struct Node
	{
		int data;
		Node* left, *right;
	};
	Node* root;
	Print* prnt;

private:
	class Print
	{
	public:
		Print(BST* _bst)
		{
			bst = _bst;
		}

		void Preorder()
		{
			if (bst->root == nullptr)
				return;

			std::stack<Node*> nodeStk;
			nodeStk.push(bst->root);

			while (nodeStk.empty() == false)
			{
				Node* temp = nodeStk.top();
				std::cout << temp->data << " ";
				nodeStk.pop();

				if (temp->right)
					nodeStk.push(temp->right);
				if (temp->left)
					nodeStk.push(temp->left);
			}
		}

		void Inorder()
		{
			if (bst->root == nullptr)
				return;

			std::stack<Node*> nodeStk;
			nodeStk.push(bst->root);

			Node* temp = bst->root;

			while (!nodeStk.empty())
			{
				while (temp != nullptr)
				{
					nodeStk.push(temp);
					temp = temp->right;
				}
				temp = nodeStk.top();
				nodeStk.pop();

				std::cout << temp->data << " ";
				temp = temp->left;
			}
		}

		void Postorder()
		{
			if (!bst->root)
				return;

			std::stack<Node*> stk1;
			std::stack<Node*> stk2;

			stk1.push(bst->root);

			Node* temp;

			while (!stk1.empty())
			{
				temp = stk1.top();
				stk1.pop();
				stk2.push(temp);

				if (temp->left)
					stk1.push(temp->left);
				if (temp->right)
					stk1.push(temp->right);
			}
			while (!stk2.empty())
			{
				temp = stk2.top();
				stk2.pop();

				std::cout << temp->data << " ";
			}
		}

	private:
		BST * bst;
	};
};

int main()
{
	BST* bst = new BST(15);
	bst->add(25);
	bst->add(10);
	bst->add(12);
	bst->add(5);
	bst->add(23);
	bst->add(50);

	bst->print().Postorder();

	std::cout <<std::endl<<bst->find(50);
	getchar();
	return 0;
}
