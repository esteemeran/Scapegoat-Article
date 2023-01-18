//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Node
{
public:
	Node *left, *right, *parent;
	float value;
	Node(float v)
	{
		value = v;
		left = right = parent = NULL;
	}
};
// Global root pointer 
Node *root;
class ScapeGoatTree
{
public:
	int n, q;
	ScapeGoatTree() {
		root = NULL;
		n = 0;
		q = 0;
	}

	int size(Node *node)
	{
		if (node == NULL)
			return 0;
		return 1 + size(node->left) + size(node->right);
	}

	int log32(int q)
	{
		return (int)(log(q) / log(1.5));
	}

	bool search(Node *r, float val)
	{
		while (r != NULL)
		{
			int rval = r->value;
			if (val < rval)
				r = r->left;
			else if (val > rval)
				r = r->right;
			else
				return true;
		}
		return false;
	}

	void inorder(Node *r)
	{
		if (r != NULL)
		{
			inorder(r->left);
			cout << r->value << "   ";
			inorder(r->right);
		}
	}

	void preorder(Node *r)
	{
		if (r != NULL)
		{
			cout << r->value << "   ";
			preorder(r->left);
			preorder(r->right);
		}
	}

	void postorder(Node *r)
	{
		if (r != NULL)
		{
			postorder(r->left);
			postorder(r->right);
			cout << r->value << "   ";
		}
	}

	void levelorder(Node *r)
	{
		if (!r)
		{
			return;
		}
		queue <Node *> q;
		q.push(r);
		cout << endl;
		while (!q.empty())
		{
			int s = q.size();
			while (s--)
			{
				auto p = q.front();
				q.pop();
				cout << p->value << " ";
				if (p->left)
					q.push(p->left);
				if (p->right)
					q.push(p->right);
			}
			cout << endl;
		}
	}

	bool insert(float x)
	{

		Node *node = new Node(x);
		int d = addWithDepth(node);
		// cout<<d<<" "<<log32(q)<<" ";
		if (d > log32(q))
		{
			Node *p = node->parent;
			while (3 * size(p) <= 2 * size(p->parent))
				p = p->parent;

			rebuildTree(p->parent);
		}

		return d >= 0;
	}

	vector <Node *> arr;
	int makeArrayofPointers(Node *ptr, int i)
	{
		if (!ptr)
			return i;

		i = makeArrayofPointers(ptr->left, i);
		arr[i++] = ptr;
		return makeArrayofPointers(ptr->right, i);
	}


	void rebuildTree(Node *u)
	{
		int n = size(u);
		Node *p = u->parent;
		arr.resize(n);
		makeArrayofPointers(u, 0);
		//sort(arr.begin(), arr.end(), [](Node *aa, Node* bb) { return aa->value < bb->value; });
		//for(auto i:arr)
		//{
		  //  cout<<i->value<<" ";
		//}
		if (p == NULL)
		{
			root = buildBalancedTree(0, n);
			root->parent = NULL;
		}
		else if (p->right == u)
		{
			p->right = buildBalancedTree(0, n);
			p->right->parent = p;
		}
		else
		{
			p->left = buildBalancedTree(0, n);
			p->left->parent = p;
		}
	}

	Node * buildBalancedTree(int i, int n)
	{
		if (n == 0)
			return NULL;
		int m = n / 2;

		arr[i + m]->left = buildBalancedTree(i, m);

		if (arr[i + m]->left != NULL)
			arr[i + m]->left->parent = arr[i + m];

		arr[i + m]->right =
			buildBalancedTree(i + m + 1, n - m - 1);
		if (arr[i + m]->right != NULL)
			arr[i + m]->right->parent = arr[i + m];

		return arr[i + m];
	}

	int addWithDepth(Node *u)
	{
		Node *temp_root = root;
		if (temp_root == NULL)
		{
			root = u;
			n++;
			q++;
			return 0;
		}
		bool done = false;
		int d = 0;
		do
		{
			if (u->value < temp_root->value)
			{
				if (temp_root->left == NULL)
				{
					temp_root->left = u;
					u->parent = temp_root;
					done = true;
				}
				else
					temp_root = temp_root->left;
			}
			else if (u->value > temp_root->value)
			{
				if (temp_root->right == NULL)
				{
					temp_root->right = u;
					u->parent = temp_root;
					done = true;
				}
				else
					temp_root = temp_root->right;
			}
			else
				return -1;
			d++;
		} while (!done);

		n++;
		q++;
		return d;
	}

	Node *inorderPred(Node *r)
	{
		r = r->left;
		while (r->right)
		{
			r = r->right;
		}
		return r;
	}

	Node* deleteBST(Node *r, float key)
	{
		if (!r)
			return NULL;
		if (r->value > key)
		{
			r->left = deleteBST(r->left, key);
		}
		else if (r->value < key)
		{
			r->right = deleteBST(r->right, key);
		}
		else
		{
			if (!r->left)
			{
				Node* temp = r->right;
				return temp;
			}
			else if (!r->right)
			{
				Node* temp = r->left;
				return temp;
			}
			Node *temp = inorderPred(r);
			r->value = temp->value;
			r->left = deleteBST(r->left, temp->value);
		}
		return r;
	}

	void deleteNode(Node *r, float key)
	{
		if (search(r, key))
		{
			root = deleteBST(r, key);
			n--;
			if (q > 2 * n)
			{
				rebuildTree(root);
				q = n;
			}
			cout << key << " is deleted." << endl;
			levelorder(root);
		}
		else
			cout << "Element not found." << endl;
	}
};

enum interface
{
	Interface,
	Insert, 
	Search,
	Delete,
	Display_Tree,
	End,
	Open
};
void PrintInterface()
{
	cout << "\nScapeGoat Tree Operations\n";
	cout << interface::Open << ". Open file " << endl;
	cout << interface::Insert << ". Insert " << endl;
	cout << interface::Search << ". Search" << endl;
	cout << interface::Delete << ". Delete" << endl;
	cout << interface::Display_Tree << ". Display Tree" << endl;
	cout << interface::Interface << ". Display Interface" << endl;
	cout << interface::End << ". End" << endl;
}

void timeCounter(time_point<steady_clock> start)
{
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << duration.count() << " microseconds" << endl;
}

void displayTree(ScapeGoatTree &sgt)
{
	cout << "\nPost order : ";
	sgt.postorder(root);
	cout << "\nPre order : ";
	sgt.preorder(root);
	cout << "\nIn order : ";
	sgt.inorder(root);
	cout << "\nLevel order : ";
	sgt.levelorder(root);
}
void autoInteract(ifstream &input, ScapeGoatTree &sgt)
{
	float val;
	int choice;
	while (input >> choice)
	{
		switch (choice)
		{
			case interface::Insert :
				input >> val;
				sgt.insert(val);
				break;

				case interface::Search :
					input >> val;
					if (sgt.search(root, val))
						cout << val << " Element is found in the tree" << endl;
					else
						cout << val << " Element is not found" << endl;
					break;

					case interface::Delete :
						input >> val;
						sgt.deleteNode(root, val);

						case interface::Display_Tree :
							displayTree(sgt);
							break;
		}
	}

}
void NormalInteract(ScapeGoatTree &sgt)
{
	ifstream input;
	string fileName = "";

	float val;
	int choice;
	int file = 0;
	time_point<steady_clock> start;
	PrintInterface();
	do
	{
		cout << "Enter your Choice: ";
		cin >> choice;
		switch (choice)
		{
			case interface::Interface :
				PrintInterface();
				break;

				case interface::End :
						break;

					case interface::Display_Tree :
						start = high_resolution_clock::now();
						displayTree(sgt);
						timeCounter(start);
					break;

						case interface::Open :
							cout << "Enter local file name: ";
							cin >> fileName;
							input.open(fileName);
							if (input)
							{
								start = high_resolution_clock::now();
								autoInteract(input, sgt);
								timeCounter(start);
							}
							else cout << "Can't open the file" << endl;
							break;

							case interface::Insert :
								cout << "Enter integer element to insert: ";
								cin >> val;
								start = high_resolution_clock::now();
								sgt.insert(val);
								timeCounter(start);
								break;

								case interface::Search :
									cout << "Enter integer element to search: ";
									cin >> val;

									start = high_resolution_clock::now();
									if (sgt.search(root, val))
										cout << val << " Element is found in the tree" << endl;
									else
										cout << val << " Element is not found" << endl;
									timeCounter(start);
									break;

									case interface::Delete :
										cout << "Enter integer element to delete: ";
										cin >> val;
										start = high_resolution_clock::now();
										sgt.deleteNode(root, val);
										timeCounter(start);
										break;

									default: break;

		}
	} while (choice != interface::End);
	input.close();
}

int main()
{
	ScapeGoatTree sgt;
	NormalInteract(sgt);
	return 0;
}