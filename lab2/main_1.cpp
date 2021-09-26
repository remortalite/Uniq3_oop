#include <iostream>
#include <random>
#include <ctime>

int **makeRandMatrix(int size, int maxValue) {
	int **matrix = new int*[size];
	for (int i = 0; i < size; ++i) {
		matrix[i] = new int[size];
		for (int j = 0; j < size; ++j) {
			matrix[i][j] = rand() % maxValue;
		}
	}
	return matrix;
}

void print(int **matrix, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			printf("%-4d ", matrix[i][j]);
		}
		std::cout << std::endl;
	}
}

int main() {
	int N = 11;
		
	int **matrix = makeRandMatrix(N, 123);
	print(matrix, N);

	int *D = new int[N*N];

	int row = 1;
	int col = N-1;
	int left = 1;
	int k = N-1, t = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
				D[i*N+j] = matrix[t][k];
				t++;
				k--;
				if (left) {
					if (k == 0-1) {
						t = 0;
						k = --col;
					} 
					if (k == 0-1 && t == 0) {
						left = 0;
						t = row;
						k = N-1;
					}
				} else {
					if (t == N) {
						t = ++row;
						k = N-1;
					}
				}
		}
	}
	putchar('\n'); putchar('\n');
	for (int i = 0; i < N*N; ++i) printf("%d ", D[i]);

	k = 0; t = 0;
	row = 0; col = 0;
	left = 1;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
				D[i*N+j] = matrix[t][k];
				t++;
				k++;
				if (left) {
					if (k == N) {
						t = 0;
						k = ++col;
					} 
					if (k == N && t == 0) {
						left = 0;
						t = ++row;
						k = 0;
					}
				} else {
					if (t == N) {
						t = ++row;
						k = 0;
					}
				}
		}
	}
	putchar('\n'); putchar('\n');
	for (int i = 0; i < N*N; ++i) printf("%d ", D[i]);
	putchar('\n'); putchar('\n');

	int idxRow, idxCol;
	idxRow = idxCol = (N-1) / 2;
	int cRow = 1, cCol = 0;
	int sign = 1;
	int count = 0;
	int repeats = 1;
	int tempRepeats = repeats;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			//printf("idx (%d %d) : %d\n", idxRow, idxCol, matrix[idxRow][idxCol]);
			//printf("tempRep: %d\n", tempRepeats);
			D[i*N+j] = matrix[idxRow][idxCol];
			--tempRepeats;
			idxRow += sign*cRow;
			idxCol += sign*cCol;
			if (tempRepeats == 0) {
				++count;
				cRow = 1 - cRow;
				cCol = 1 - cCol;
				if (count%2==0) {
					sign *= -1;
					++repeats;
					//printf("\nrepeats: %d\nsign: %d\n", repeats,sign);
				}
				tempRepeats = repeats;
			}
		}
	}
	for (int i = 0; i < N*N; ++i) printf("%d ", D[i]); 
	putchar('\n'); putchar('\n');

	idxRow = idxCol = 0;
	int step = 0;
	int tempStep = step;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			//printf("\nidx (%d %d) : %d\n", idxRow, idxCol, matrix[idxRow][idxCol]);
			//printf("step: %d\n", step);
			//printf("tempStep: %d\n", tempStep);
			D[i*N+j] = matrix[idxRow][idxCol];

			if (idxCol == 0) {
				++step;
				idxRow = 0;
				idxCol = step;
				tempStep = step;
			} else {
				if (tempStep) {
					++idxRow; 
					--tempStep;
				} else {
					--idxCol;
				}
			}
		}
	}
	for (int i = 0; i < N*N; ++i) printf("%d ", D[i]); 
	putchar('\n'); putchar('\n');

	return 0;
}
