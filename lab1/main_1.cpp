#include <iostream>
#include <random>
#include <ctime>

int* getRandArray(int size, int maxValue) {
	int *arr = new int[size+1];
	arr[0] = size;
	for (int i = 1; i <= size; ++i) {
		arr[i] = rand() % maxValue;
	}	
	return arr;
}
void print(int *arr) {
	int size = arr[0];
	std::cout << size << ": ";
	for (int i = 1; i <= size; ++i) {
		std::cout << arr[i] << " ";
	}	
	std::cout << std::endl;
}

int main() {
	srand(time(0));
	int size = rand() % 10;
	int maxValue = 100;
	int *arr = getRandArray(size, maxValue);
	print(arr);
	delete[] arr;
	return 0;
}
