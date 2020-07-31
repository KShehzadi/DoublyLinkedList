#include <fstream>
#include <iostream>
using namespace std;


class node
{
	public:
		int data;
		node * left;
    node * right;
		int key = data;
		node();
node(int data);
node(const node& node);
int CompareWith(const node& n);
int GetKey();
void ReadFromFile(ifstream &infile);
void WriteToFile(ofstream &ofile);
void print();
};


node::node():data(0), left(NULL), right(NULL)
{

}

node::node(int data):data(data), left(NULL), right(NULL)
{

}

node::node(const node& n):data(n.data), left(NULL), right(NULL)
{

}

int node::CompareWith(const node& n)
{
  if(this->key > n.key) return 1;
  if(this->key == n.key) return 0;
  if(this->key < n.key) return -1;
}

void node::ReadFromFile(ifstream &infile)
{
  infile.read((char*) &this->data, sizeof(this->data));
}

void node::WriteToFile(ofstream &ofile)
{
  ofile.write((char*) &this->data, sizeof(this->data));
}

void node::print()
{
  cout<<this->data;
}

class DLinkedList
{
protected:
	int count;
		node * righthead;
		node * lefthead;
public:
		DLinkedList();
		~DLinkedList();
		DLinkedList(node * &n);
		void insertleft(node *& n);
		void insertright(node *& n);
		void insertAtFromLeft(int index, node *& n);
		void insertAtFromRight(int index, node *& n);
		void printl();
		void deletenode(int v);
    void deleter();
		void deletel();
		void printr();
		int searchl(int v);
		int searchr(int v);
};

DLinkedList::DLinkedList()
{
	lefthead = NULL;
	righthead = NULL;
	count = 0;
}
DLinkedList::DLinkedList(node *& n)
{
	count = 1;
	lefthead = n;
	righthead = n;
	righthead->left = lefthead;
	lefthead->right = righthead;
	n = NULL;
}
void DLinkedList::insertright(node *& n)
{
	n->left = righthead;
	if(righthead)
	{
		righthead->right = n;
		righthead = n;

	}
	else{
		righthead = n;
		lefthead = n;
	}
	righthead->right = NULL;
	n = NULL;
	count++;
}
void DLinkedList::insertleft(node *& n)
{
	n->right = lefthead;
	if(lefthead)
	{
		lefthead->left = n;
		lefthead = n;
	}
	else{
		lefthead = n;
		righthead = n;
	}
	lefthead->left = NULL;
	n = NULL;
	count++;
}






void DLinkedList::insertAtFromLeft(int index, node*&n)
{
	if(index <= 0)
	{
		this->insertleft(n);
	}
	else if(index >= count)
	{
		this->insertright(n);
	}
	else
	{
		node * rp;
		int i, steps;
		if(index < count/2)
		{
			rp = lefthead;
			for(i = 1; i < index; ++i)
			{
				rp = rp->right;
			}
		}
		else
		{
			steps = count - index;
			rp = righthead;
			for(i = 0; i < steps; i++)
			{
				rp = rp->left;
			}
		}
		n->right = rp->right;
		n->left = rp;
		rp->right = n;
		n->right->left = n;
		this->count++;
		n = NULL;
	}
}
void DLinkedList::insertAtFromRight(int index, node*&n)
{
	if(index <= 0)
	{
		this->insertright(n);
	}
	else if(index >= count)
	{
		this->insertleft(n);
	}
	else
	{
		node * rp;
		int i, steps;
		if(index < count/2)
		{
			rp = righthead;
			for(i = 1; i < index; ++i)
			{
				rp = rp->left;
			}
		}
		else
		{
			steps = count - index;
			rp = lefthead;
			for(i = 0; i < steps; i++)
			{
				rp = rp->right;
			}
		}
		n->left = rp->left;
		n->right = rp;
		rp->left = n;
		n->left->right = n;
		this->count++;
		n = NULL;
	}
}
void DLinkedList::printl()
{
	node * tmp;
	tmp = lefthead;
	for(int i = 0; i < this->count; i++)
	{
		tmp->print();
		tmp = tmp->right;
	}
}
void DLinkedList::printr()
{
	node * tmp;
	tmp = righthead;
	for(int i = 0; i < this->count; i++)
	{
		tmp->print();
		tmp = tmp->left;
	}
}
void DLinkedList::deletel()
{
	if(lefthead == NULL)
	{
		return;
	}
	else if(lefthead != NULL && lefthead == righthead)
	{
		node * tmp;
		tmp = lefthead;
		delete tmp;
		lefthead = NULL;
		righthead = NULL;
		count = 0;
	}
	else
	{
		node * tmp = lefthead;
		lefthead = lefthead->right;
		lefthead->left = NULL;
		tmp->right = NULL;
		delete tmp;
		count--;
	}
}
void DLinkedList::deleter()
{
	if(righthead == NULL)
	{
		return;
	}
	else if(righthead != NULL && righthead == lefthead)
	{
		node * tmp;
		tmp = lefthead;
		delete tmp;
		lefthead = NULL;
		righthead = NULL;
		count = 0;
	}
	else
	{
		node * tmp = righthead;
		righthead = righthead->left;
		righthead->right = NULL;
		tmp->left = NULL;
		delete tmp;
		count--;
	}
}
void DLinkedList::deletenode(int v)
{
	node * tmp;
	if(lefthead == NULL || righthead == NULL)
	{
		return;
	}
	if(lefthead != NULL && lefthead->data == v)
	{
		tmp = lefthead;
		lefthead = lefthead->right;
		if(lefthead){lefthead->left = NULL;}
		tmp->right = NULL;
		delete tmp;
	}
	else if(righthead != NULL && righthead->data == v)
	{
		tmp = righthead;
		righthead = righthead->left;
		if(righthead){righthead->right = NULL;}
		tmp->left = NULL;
		delete tmp;
	}
	else
	{
		tmp = lefthead;
		for(int i = 0; i < count; i++)
		{
			if(tmp->data == v)
			{
				tmp->left->right = tmp->right;
				tmp->right->left = tmp->left;
				tmp->left = tmp->right = NULL;
				delete tmp;
				break;
			}
			tmp = tmp->right;
		}
	}
	this->count--;
}
int DLinkedList::searchr(int v)
{
	node * np = righthead;
	for(int i = 0; i < count; i++)
	{
		if(np->data == v)
		{
			return i;
		}
		np = np->left;
	}
	return -1;
}
int DLinkedList::searchl(int v)
{
	node * np = lefthead;
	for(int i = 0; i < count; i++)
	{
		if(np->data == v)
		{
			return i;
		}
		np = np->right;
	}
	return -1;
}
DLinkedList::~DLinkedList()
{}






int main()
{
	node* ptr1 = new node(1);
  node* ptr2 = new node(2);
  node* ptr3 = new node(3);
  node* ptr4 = new node(4);
  node* ptr5 = new node(5);

  DLinkedList C1;
	cout<< "%%%%%%%%%%%%%%%%% INSERTION FROM LEFT %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<< endl;
	cout<< "checkin insertion method from left and inserting 1, 2, 3, 4 and 5 node in same order"<< endl;
  C1.insertleft(ptr1);
  C1.insertleft(ptr2);
  C1.insertleft(ptr3);
  C1.insertleft(ptr4);
  C1.insertleft(ptr5);
	cout << "printing from right"<< endl;
	C1.printr();
	cout<< endl;
	cout << "printing from left"<< endl;
	C1.printl();



	node* ptr6 = new node(1);
  node* ptr7 = new node(2);
  node* ptr8 = new node(3);
  node* ptr9 = new node(4);
  node* ptr10 = new node(5);
	DLinkedList C2;
	cout<< endl;
	std::cout << "%%%%%%%%%%%%%%%%%%%%% INSERTION FROM RIGHT %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << '\n';
	cout<< "checkin insertion method from right and inserting 1, 2, 3, 4 and 5 node in same order"<< endl;
	C2.insertright(ptr6);
  C2.insertright(ptr7);
  C2.insertright(ptr8);
  C2.insertright(ptr9);
  C2.insertright(ptr10);
	cout << "printing from right"<< endl;
	C2.printr();
	cout<< endl;
	cout << "printing from left"<< endl;
	C2.printl();
	cout<< "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% checking deletion from left %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<< endl;
	cout << "here is the original list left to right" << '\n';
	C2.printl();
	cout<< endl<< "after first deletion"<< endl;
	C2.deletel();
	C2.printl();
	cout<< endl<< "after 2nd deletion"<< endl;
	C2.deletel();
	C2.printl();
	cout<< endl;
	cout<< "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% checking deletion from right %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<< endl;
	cout << "here is the original list from left to right" << '\n';
	C2.printl();
	cout<< endl<< "after first deletion"<< endl;
	C2.deleter();
	C2.printl();
	cout<< endl<< "after 2nd deletion"<< endl;
	C2.deleter();
	C2.printl();
	cout<< endl;
	cout<< "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% checking deletion of a node with certain value %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<< endl;
	cout << "here is the original list from left to right" << '\n';
	C1.printl();
	cout<< endl<< "deleting 1 from list"<< endl;
	C1.deletenode(1);
	C1.printl();
	cout<< endl<< "deleting 3 from list"<< endl;
	C1.deletenode(3);
	C1.printl();
	cout<< endl;
	cout<< endl<< "deleting 5 from list"<< endl;
	C1.deletenode(5);
	C1.printl();
	cout<< endl;
	node* ptr11 = new node(1);
  node* ptr22 = new node(2);
  node* ptr33 = new node(3);
  node* ptr44 = new node(4);
  node* ptr55 = new node(5);
  DLinkedList C3;
  C3.insertleft(ptr11);
  C3.insertleft(ptr22);
  C3.insertleft(ptr33);
  C3.insertleft(ptr44);
  C3.insertleft(ptr55);
	std::cout << "%%%%%%%%%%%%%%%%%%%%%% TESTING OF SEARCHING %%%%%%%%%%%%%%%%%%%%%%%%%%" << '\n';
	std::cout << "" << '\n';
	std::cout << "#################################################################" << '\n';
	std::cout << " From left to right ! '-1' means there is no such value in list" << '\n';
	int i;
	std::cout << "here is the original list" << '\n';
	C3.printl();
	std::cout << "" << '\n';
	std::cout << "searching 1 in list" << '\n';
	i = C3.searchl(1);
	std::cout << "the index of desired value in list is "<< i<<"!" << '\n';
	std::cout << "searching 4 in list" << '\n';
	i = C3.searchl(4);
	std::cout << "the index of desired value in list is "<< i<<"!" << '\n';
	std::cout << "searching 6 in list" << '\n';
	i = C3.searchl(6);
	std::cout << "the index of desired value in list is "<< i<<"!" << '\n';
	std::cout << "###################################################################" << '\n';
	std::cout << " From right to left ! '-1' means there is no such value in list" << '\n';
	std::cout << "here is the original list" << '\n';
	C3.printl();
	std::cout << "" << '\n';
	std::cout << "searching 1 in list" << '\n';
	i = C3.searchr(1);
	std::cout << "the index of desired value in list is "<< i<<"!" << '\n';
	std::cout << "searching 4 in list" << '\n';
	i = C3.searchr(4);
	std::cout << "the index of desired value in list is "<< i<<"!" << '\n';
	std::cout << "searching 6 in list" << '\n';
	i = C3.searchr(6);
	std::cout << "the index of desired value in list is "<< i<<"!" << '\n';
	node * n1 = new node(9);
	node * n2 = new node(8);
	node * n3 = new node(7);
	node * n4 = new node(6);
	node * n5 = new node(8);
	node * n6 = new node(7);
	std::cout << "%%%%%%%%%%%%% TESTING INSERTION FROM LEFT AT A CERTAIN INDEX%%%%%%%%%%%%%%%%%%%%" << '\n';
	std::cout << "here is the original list" << '\n';
	C3.printl();
	std::cout << "" << '\n';
	std::cout << "inserting 9 at index 3" << '\n';
	C3.insertAtFromLeft(3, n1);
	C3.printl();
	std::cout << "" << '\n';
	std::cout << "inserting 8 at index 0" << '\n';
	C3.insertAtFromLeft(0, n2);
	C3.printl();
	std::cout << "" << '\n';
	std::cout << "inserting 7 at index 8" << '\n';
	C3.insertAtFromLeft(8, n3);
	C3.printl();
	std::cout << "%%%%%%%%%%%%% TESTING INSERTION FROM RIGHT AT A CERTAIN INDEX%%%%%%%%%%%%%%%%%%%%" << '\n';
	std::cout << "here is the original list" << '\n';
	C3.printl();
	std::cout << "" << '\n';
	std::cout << "inserting 8 at index 4" << '\n';
	C3.insertAtFromRight(4, n5);
	C3.printl();
	std::cout << "" << '\n';
	std::cout << "inserting 6 at index 0" << '\n';
	C3.insertAtFromRight(0, n4);
	C3.printl();
	std::cout << "" << '\n';
	std::cout << "inserting 7 at index 7" << '\n';
	C3.insertAtFromRight(7, n6);
	C3.printl();
}

