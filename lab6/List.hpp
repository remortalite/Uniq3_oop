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

        Node* m_head;

        Node* createNode(int data);


public:

	List();
	List(const std::initializer_list<int> &);
	~List();

	int getId();

	void add(int data);
	void remove();

	void print();

	Node* getLast();
};

class Stack: public List
{
	
public:
	Stack();
	Stack(const std::initializer_list<int> &);

	void push(int data);
	int pop();
};




#endif // #ifndef LIST_HPP	
