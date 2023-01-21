#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <chrono>

#include "sgt.cpp"
using namespace std;
using namespace std::chrono;

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