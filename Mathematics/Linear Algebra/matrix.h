#pragma once

#include <iostream>

class matrix
{
private:
	int** _matrix = NULL;
	int _row = 0, _col = 0;
	int determinant = INT32_MIN;

public:
	matrix(int row, int col);
	matrix(matrix* source);
	matrix(int* arr, int length, int row, int col);
	~matrix();

	void printRow(int row);
	void printCol(int col);
	void printAll();

	void toUnit();
	void setValue(int row, int col, int value);
	void setRand(int row, int col, int max);
	void fillValue(int value);
	void fillRand(int max);

	void transPose();
	void addMatrix(matrix* second);
	void subtractMatrix(matrix* second);
	void multiplyMatrix(matrix* second);
	void multiplyScalar(int k);

	matrix AddedMatrix(matrix* second);
	matrix SubtractedMatrix(matrix* second);
	matrix MultipledMatrix(matrix* second);
	matrix Minor(int row, int col);
	matrix Adjacent();

	int calculateSarrus();
	int calculateDeterminant();
	int getDeterminant();

	matrix operator + (matrix& source);
	matrix operator - (matrix& source);
	matrix operator * (matrix& source);
};
