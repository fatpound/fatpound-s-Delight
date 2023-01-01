#pragma once

#include <iostream>

class matrix
{
private:
	double** _matrix = NULL;
	int _row = 0, _col = 0;
	double determinant = INT32_MIN;

public:
	matrix(int row, int col);
	matrix(matrix* source);
	matrix(double* arr, double length, int row, int col);
	~matrix();

	void printAll();
	void printRow(int row);
	void printCol(int col);

	void toUnit();
	void setValue(int row, int col, double value);
	void setRand(int row, int col, int max);
	void fillValue(double value);
	void fillRand(int max);

	void transPose();
	void addMatrix(matrix* second);
	void subtractMatrix(matrix* second);
	void multiplyMatrix(matrix* second);
	void multiplyScalar(double k);

	matrix TransPosedMatrix();
	matrix AddedMatrix(matrix* second);
	matrix SubtractedMatrix(matrix* second);
	matrix MultipledMatrix(matrix* second);
	matrix MinorMatrix(int row, int col);
	matrix AdjacentMatrix();
	matrix InverseMatrix();

	double calculateSarrus();
	double calculateDeterminant();

	matrix operator + (matrix& source);
	matrix operator - (matrix& source);
	matrix operator * (matrix& source);
};