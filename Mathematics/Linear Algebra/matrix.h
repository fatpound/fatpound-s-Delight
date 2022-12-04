#pragma once

#include <iostream>

class matrix
{
private:
	int** _matrix = NULL;
	int _row, _col;

public:
	matrix(int row, int col);
	matrix(matrix* source);
	~matrix();

	void printRow(int row);
	void printCol(int col);
	void printAll();

	void setValue(int row, int col, int value);
	void setRand(int row, int col, int max);
	void fillValue(int value);
	void fillRand(int max);

	void toUnit();
	void transPose();

	void addMatrix(matrix* second);
	void multiplyScalar(int k);
	void multiplyMatrix(matrix* second);
	matrix returnMultipledMatrix(matrix* second);

	matrix returnMinor(matrix* source, int row, int col);
	matrix returnAdj(matrix* source);
	int calculateSarrus();
	int calculateDeterminant(matrix* source);
};
