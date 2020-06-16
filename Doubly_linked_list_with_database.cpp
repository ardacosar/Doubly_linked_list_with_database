
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>

using namespace std;

struct node {

	string data;
	node* prev;
	node* next;
};

bool searchInNode(node* r, string d)
{
		node* tmp;
		tmp = r;
		do {
			if (tmp->data == d)
				return true;

			tmp = tmp->next;
		} while (tmp != r);

	return false;
}

node* removeNode(node* r, string d)
{
			node* tmp;
			tmp = r;
			do {
				tmp = tmp->next;
			} while (tmp->data != d && tmp != r);

			if (tmp->data == d)
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				
				if (tmp == r) { r = tmp->next; }
				
				tmp == NULL;
				delete tmp;

				string data;
				ifstream dRead("List.txt");
				ofstream dWrite("List2.txt", ios::app);

				while (!dRead.eof())
				{
					getline(dRead, data);
					if (data != d && data != "") { dWrite << data << endl; }
				}

				dWrite.close();
				dRead.close();
				remove("List.txt");
				rename("List2.txt", "List.txt");

				cout << "it's succesfully removed" << endl;
			}
			else { cout << "There is not" << endl; }
		
	return r;
}

node* firstNode(node* r, string d)
{
		r = new node;
		r->data = d;
		r->next = r;
		r->prev = r;
		return r;
}

void writeToFile(string d)
{
	ofstream dWrite("List.txt", ios::app);
	dWrite << d << endl;;
	cout << "it's done." << endl;
	dWrite.close();
}

node* addNode(node* r, string d, bool inFile)
{
	if (r == NULL) 
	{
		r = firstNode(r, d);
		if (!inFile)
		{ writeToFile(d); }
	}
	else if(!searchInNode(r, d))
	{
			node* tmp;
			tmp = new node;
			tmp->data = d;

			tmp->prev = r->prev;
			tmp->next = r;

			r->prev->next = tmp;		
			r->prev = tmp;
			

			tmp = NULL;
			delete tmp;

			if (!inFile) // if there is not in database, add  to database
			{ writeToFile(d); }		
	}
	else { cout << "it's already exist." << endl; }
	

	return r;
}

node* listToNodes(node* r) // all datas in database transfer to linked structure
{
	string data;
	ifstream dRead("List.txt");
	if (dRead)
	{
	 while (!dRead.eof())   
	 {
		getline(dRead, data);
		if (data != "") { r = addNode(r, data, true); }
	 }	
	}
	else // create if there is not a database
	{
		ofstream cre("List.txt");
		cre.close();
	}
	dRead.close();
	return r;
}

void getNodes(node* r)
{
     while (true)
	 {
		system("cls");
		
			cout << "Commands: " << endl << "Right Arrow - Next data" << endl << "Left Arrow - Previous data" << endl << "Down Arrow - Back to menu" << endl;
			cout << r->data;
			system("pause>nul");
			if (GetAsyncKeyState(VK_RIGHT)) { r = r->next; }	// if pressing right arrow key
			if (GetAsyncKeyState(VK_LEFT)) { r = r->prev; }		// if pressing left arrow key
			if (GetAsyncKeyState(VK_DOWN)) { break; }	        // if pressing down arrow key					
	 }
	 
	
}

void menu()
{
	system("cls");

	node* root;
	root = NULL;
	root = listToNodes(root);

	char opt;
	do
	{
		system("cls");
		cout << "Commands: " << endl << "G : Get list" << endl << "A : Add to list" << endl << "R : Remove from list" << endl << "S : Search in list" << endl << "X : Exit" << endl;
		opt = _getch(); 
		if (root == NULL && opt !='a')
		{
			system("cls");
			cout << "No data found! You must add data first." << endl;
			opt = '.';
			system("pause>nul");
		}

	} while (opt != 'g' && opt != 'a' && opt != 'r' && opt != 's' && opt != 'x');

	system("cls");
	string idata;
	switch (opt)
	{
	case 'g':
		getNodes(root);
		menu();
		break;
	case 'a':
		cout << " What do you want to add?" << endl;
		cin >> idata;
		root = addNode(root, idata, false);
		system("pause");
		menu();
		break;
	case 'r':
		cout << " What do you want to remove?" << endl;
		cin >> idata;
		root = removeNode(root, idata);
		system("pause");
		menu();
		break;
	case 's':
		cout << " What do you want to find?" << endl;
		cin >> idata;
		if (searchInNode(root, idata)) { cout << "There is." << endl; }
		else						   { cout << "There is not." << endl; }
		system("pause");
		menu();
		break;
	case 'x':
		break;
	}
}

int main()
{
	menu();
}
