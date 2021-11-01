#include "List.hpp"

#include <iostream>
#include <string>

ListException::ListException(std::string error)
        : m_error(error)
{
}

const char* ListException::what() const noexcept { return m_error.c_str(); }

Node* List::createNode(int data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;
        return newNode;
}

Node* List::getLast() {
        Node* p;
        for (p = m_head; p && p->next; p = p->next) ;
        return p;
}

List::List() {
        m_head = nullptr;
        m_id = s_nextId++;
}

List::List(const std::initializer_list<int> &initList)
        : List()
{
        for (auto &data : initList)
                List::add(data);
}

List::~List() {
        Node *p, *prev;
        for (p = m_head; p; ) {
                prev = p;
                p = p->next;
                delete prev;
        }
}

int List::getId() {
        std::cout << "Id: " << m_id << std::endl;
        return m_id;
}

void List::add(int data) {
        Node* last = getLast();
        if (last)
                last->next = createNode(data);
        else
                m_head = createNode(data);
}

void List::remove() {
        Node* last = getLast();
        if (last == nullptr)
                throw ListException("Can't remove from an empty list!");
        if (last == m_head) {
                m_head = nullptr;
                return;
        }
        Node* preLast;
        for (preLast = m_head;
                preLast && preLast != last && preLast->next != last;
                preLast = preLast->next) ;
        preLast->next = nullptr;
        delete last;
}

void List::print() {
        if (m_head) {
                for (Node* p = m_head; p; p = p->next) {
                        std::cout << p->data << " ";
                }
        } else {
                std::cout << "(empty)";
        }
        std::cout << std::endl;
}

int List::s_nextId = 0;

Stack::Stack() 
	: List()
{
}

Stack::Stack(const std::initializer_list<int> &list)
	: List(list)
{
}

void Stack::push(int data) {
	List::add(data);
}

int Stack::pop() {
	Node* last = getLast();
	int data;
	if (last) {
		data = last->data;
		List::remove();
		return data;
	} else {
		throw ListException("No elements in stack!");
	}
}

