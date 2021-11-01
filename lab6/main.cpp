#include "List.hpp"

#include <iostream>
#include <string>

int main() {
	List list;
	list.add(4);
	list.print();

	List list2 {1, 2, 3, 4, 5, 6};
	list2.print();

	List list3;
	try {
		list3.remove();
	}
	catch (ListException &e)
	{
		std::cerr << "Error!: " << e.what() << "\n";
	}

	list.getId();
	list2.getId();
	list3.getId();

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

	return 0;
}
