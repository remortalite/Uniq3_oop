#define MAXEL 11

#include <iostream>
#include <random>
#include <ctime>

/**** from main_1.cpp */
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
/****/

int **getRandMatrix(int size, int maxValue) {
	int **matrix = new int*[size];
	for (int i = 0; i < size; ++i) {
		matrix[i] = getRandArray(rand() % 10, maxValue);		
	}
	return matrix;
}

void printMatrix(int **matrix, int size) {
	//int size = sizeof(matrix);
	std::cout << size << std::endl;
	for (int i = 0; i < size; ++i) {
		print(matrix[i]);
	}
}

int main() {
	srand(time(0));
	int size = rand() % 10;
	int maxValue = 100;
	int **matrix = getRandMatrix(size, maxValue);
	printMatrix(matrix, size);
		
	for (int i = 0; i < size; ++i)
		delete[] matrix[i];
	return 0;
}
