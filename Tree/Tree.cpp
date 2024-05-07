#include <iostream>
#include <set>
using namespace std;
class Student
{
public:
	std::string name;
	int age;

	Student(std::string name, int age) {
		SetName(name);
		SetAge(age);
	}
	void SetName(string name)
	{
		this->name = name;
	}
	void SetAge(int age)
	{
		this->age = age;
	}


	bool operator<(const Student& other) const {
		return age < other.age; // сравниваем студентов по возрасту
	}
};


class Tree
{
public:
	struct Node // one element of the tree
	{
		int value; // useful data

		Node* parent = nullptr;
		Node* right = nullptr;
		Node* left = nullptr;

		void ShowNode() const
		{
			cout << value << ", ";
		}
	};

private:
	Node* root = nullptr;
	// int count;

public:
	bool IsEmpty() const
	{
		return root == nullptr;
	}

	Tree() {} // так как в классе есть явно объявленный конструктор копирования, приходится и конструктор без параметров явно делать :)

	~Tree()
	{
		Clear();
	}

private:
	void ShowTree(Node* element) const
	{
		if (element != 0)
		{
			ShowTree(element->left);
			element->ShowNode();
			ShowTree(element->right);
		}
	}

public:
	void ShowTree() const
	{
		cout << "\n";
		ShowTree(root);
		cout << "\n";
	}

private:
	Node* GetRoot() const
	{
		return root;
	}

	int GetCount(Node* element, int count) const
	{
		if (element != 0)
		{
			count = GetCount(element->left, count);
			count++;
			count = GetCount(element->right, count);
		}
		return count;
	}

public:
	int GetCount() const
	{
		int count = 0;
		count = GetCount(root, count);
		return count;
	}

private:
	void Clear(Node* element)
	{
		if (element != nullptr)
		{
			Clear(element->left);
			Clear(element->right);
			delete element;
			element = nullptr;
		}
	}

public:
	void Clear()
	{
		if (!IsEmpty())
		{
			Clear(root);
			root = nullptr;
		}
	}

	Node* FindNode(int value) const
	{
		if (IsEmpty())
			return nullptr;

		Node* f = root;
		while (true)
		{
			if (value < f->value)
			{
				if (f->left != nullptr)
					f = f->left;
				else
					break;
			}
			else if (value > f->value)
			{
				if (f->right != nullptr)
					f = f->right;
				else
					break;
			}
			else
				return f;
		}
		return nullptr;
	}

	void AddNode(int value)
	{
		if (FindNode(value))
			return;

		Node* n = new Node;
		n->value = value;
		Node* parent = nullptr;
		if (IsEmpty())
		{
			root = n;
			root->parent = parent;
		}
		else
		{
			Node* p = root;
			while (p != nullptr)
			{
				parent = p;
				if (n->value > p->value)
					p = p->right;
				else
					p = p->left;
			}
			if (n->value < parent->value)
				parent->left = n;
			else
				parent->right = n;
			n->parent = parent;
		}
	}

	Tree& operator = (const Tree& original)
	{
		if (!IsEmpty())
			Clear();

		AddNode(original.root->value);
		Copy(original.root);
		return *this;
	}

	Tree(const Tree& original)
	{
		AddNode(original.root->value);
		Copy(original.root);
	}

	void Copy(Node* element)
	{
		if (element->left != nullptr)
			AddNode(element->left->value);

		if (element->right != nullptr)
			AddNode(element->right->value);

		if (element->left != nullptr)
			Copy(element->left);

		if (element->right != nullptr)
			Copy(element->right);
	}

	void DeleteNode(int value)
	{
		Node* d = FindNode(value);
		if (d == nullptr)
			return;

		Node* parent = d->parent;
		if (d == root && GetCount() == 1)
		{
			Clear();
			return;
		}
		if (d->left == nullptr && d->right == nullptr)
		{
			if (parent->left == d)
				parent->left = nullptr;
			else
				parent->right = nullptr;
			delete d;
			return;
		}
		if (d->left == nullptr && d->right != nullptr)
		{
			if (parent->left == d)
			{
				parent->left = d->right;
			}
			else
			{
				parent->right = d->right;
			}
			d->right->parent = parent;
			delete d;
			return;
		}

		if (d->left != nullptr && d->right == nullptr)
		{
			if (parent->left == d)
			{
				parent->left = d->left;
			}
			else
			{
				parent->right = d->left;
			}
			d->left->parent = parent;
			delete d;
			return;
		}
		if (d->left != nullptr && d->right != nullptr)
		{
			Node* r = d->right;
			if (r->right == nullptr && r->left == nullptr)
			{
				d->value = r->value;
				d->right = nullptr;
				delete r;
			}
			else if (r->left != nullptr)
			{
				Node* p = r->left;
				while (p->left != nullptr)
					p = p->left;
				d->value = p->value;
				if (p->right == nullptr)
					p->parent->left = nullptr;
				else
					p->parent->left = p->right;
				delete p;
			}
			else
			{
				d->value = r->value;
				d->right = r->right;
				delete r;
			}
		}
	}
};


int main()
{

	set<Student> tree;
	tree.insert(Student("Masha", 32));
	tree.insert(Student("Misha", 28));
	tree.insert(Student("Sasha", 30));
	tree.insert(Student("Dasha", 25));
	tree.insert(Student("Moysha", 35));
	tree.insert(Student("Alex", 35));

	for (Student student : tree)
	{
		cout << student.name << "\n";
		cout << student.age << "\n\n";
	}

}