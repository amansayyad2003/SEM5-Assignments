#include <stdio.h>

#define SIZE 1023 


int main(){
	int matrix1[SIZE][SIZE];
	int matrix2[SIZE][SIZE];

	int matrix[SIZE][SIZE];

	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			matrix[i][j] = 0;
		}
	}

	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			matrix1[i][j] = 1*2;
			matrix2[i][j] = 1*5;
		}
	}
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			for(int k = 0; k < SIZE; k++){
				matrix[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}

	return 0;
}
