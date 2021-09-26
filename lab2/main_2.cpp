#include <iostream>

#define N 10

void fillArray(int *array) {
	int size = array[0];
	for (int i = 0; i < size; ++i) {
		array[i+1] = rand() % 30;
	}
}

int main() {
	printf("Lab2_2\n");	

	int **arr = new int*[N];
	printf("Let's fill it up.\n");
	printf("Enter the number of elements in:\n");

	int n;
	for (int i = 0; i < N; ++i) {
		printf("array %2d: ", i);
		scanf("%d", &n);
		arr[i] = new int[n+1];
		arr[i][0] = n;
		fillArray(arr[i]);
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < arr[i][0]; ++j) {
			printf("%-3d ", arr[i][j+1]);
		}
		putchar('\n');
	}

	return 0;
}
