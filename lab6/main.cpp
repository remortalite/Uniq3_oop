#include "List.hpp"

#include <iostream>
#include <string>

int main() {

	List list2 {1, 2, 3, 4, 5, 6};
	list2.print();
	list2.add(-1);
	list2.print();

	List list3;
	try {
		list3.remove();
	}
	catch (ListException &e)
	{
		std::cerr << "Error!: " << e.what() << "\n";
	}

	list2.getId();
	list3.getId();

	std::cout << "\nStack: " << std::endl;
	Stack stack {1};

	stack.print();
	stack.push(2);
	stack.print();
	stack.push(2);
	stack.print();
	std::cout << "Pop: " << stack.pop() << std::endl;
	std::cout << "Pop: " << stack.pop() << std::endl;
	std::cout << "Pop: " << stack.pop() << std::endl;
	stack.print();

	try {
		stack.pop();
	}
	catch (ListException &e)
	{
		std::cerr << "Error! " << e.what() << std::endl;
	}

	std::cout << "\nQue: " << std::endl;
	Que que {1, 3, 5, 7, 9};

	que.print();
	que.push(-1);
	que.print();
	que.push(-2);
	que.print();
	que.pop();
	que.print();
	que.pop();
	que.print();
	que.pop();
	que.print();
	que.pop();
	que.print();
	que.pop();
	que.print();
	que.pop();
	que.print();
	que.pop();
	que.print();

	try {
		que.pop();
	}
	catch (ListException &e)
	{
		std::cerr << "Error!: " << e.what() << "\n";
	}

	return 0;
}
