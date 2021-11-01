#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <string>

typedef struct Node {
        struct Node* next;
        int data;
} Node;

class ListException: public std::exception
{
        std::string m_error;

public:
        ListException(std::string error);

        const char* what() const noexcept;
};

class List
{
        static int s_nextId;
        int m_id;


        Node* createNode(int data);

protected:
        Node* m_head;

public:

	List();
	List(const std::initializer_list<int> &);
	~List();

	int getId();

	Node* add(int data);
	void remove();

	void print();

	Node* getLast();
	Node* getFirst();
};

class Stack: public List
{
	
public:
	Stack();
	Stack(const std::initializer_list<int> &);

	void push(int data);
	int pop();
};

class Que: public Stack
{

protected:
	Node* m_tail;

public:
	Que();
	Que(const std::initializer_list<int> &);

	void push(int);
	int pop();
};


#endif // #ifndef LIST_HPP	
