#include <iostream>
#include <cstdlib>
#include <ctime>

#include "matrix.h"

using namespace std;

matrix::matrix(int row, int col)
{
	if (row < 1 || col < 1)
	{
		return;
	}

	srand(time(NULL));

	_row = row;
	_col = col;

	_matrix = new double* [_row];

	for (int i = 0; i < _row; i++)
	{
		_matrix[i] = new double[_col];
	}
}
matrix::matrix(matrix* source)
{
	srand(time(NULL));

	_row = source->_row;
	_col = source->_col;

	_matrix = new double* [_row];

	for (int i = 0; i < _row; i++)
	{
		_matrix[i] = new double[_col];
	}

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			_matrix[i][j] = source->_matrix[i][j];
		}
	}
}
matrix::matrix(double* arr, double length, int row, int col)
{
	if (row * col != length)
	{
		return;
	}

	_row = row;
	_col = col;

	_matrix = new double* [_row];

	for (int i = 0; i < _row; i++)
	{
		_matrix[i] = new double[_col];
	}

	int n = 0;

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			_matrix[i][j] = arr[n++];
		}
	}
}
matrix::~matrix()
{

}

void matrix::printAll()
{
	for (int i = 0; i < _row; i++, cout << "\n")
	{
		for (int j = 0; j < _col; j++)
		{
			cout << _matrix[i][j] << " ";
		}
	}

	cout << "\n";
}
void matrix::printRow(int row)
{
	for (int i = 0; i < _col; i++)
	{
		cout << _matrix[row][i] << " ";
	}

	cout << "\n";
}
void matrix::printCol(int col)
{
	for (int i = 0; i < _row; i++)
	{
		cout << _matrix[i][col] << "\n";
	}
}

void matrix::toUnit()
{
	if (_row != _col)
	{
		return;
	}

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			if (i == j && _matrix[i][j] != 1)
			{
				_matrix[i][j] = 1;
			}
			else if (_matrix[i][j] != 0)
			{
				_matrix[i][j] = 0;
			}
		}
	}
}
void matrix::setValue(int row, int col, double value)
{
	_matrix[row][col] = value;
}
void matrix::setRand(int row, int col, int max)
{
	_matrix[row][col] = rand() % ++max;
}
void matrix::fillValue(double value)
{
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			_matrix[i][j] = value;
		}
	}
}
void matrix::fillRand(int max)
{
	max++;

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			_matrix[i][j] = rand() % max;
		}
	}
}

void matrix::transPose()
{
	double** temp_matrix = new double* [_col];

	for (int k = 0; k < _col; k++)
	{
		temp_matrix[k] = new double[_row];
	}

	for (int j = 0; j < _col; j++)
	{
		for (int i = 0; i < _row; i++)
		{
			temp_matrix[j][i] = _matrix[i][j];
		}
	}

	_matrix = temp_matrix;
}
void matrix::addMatrix(matrix* second)
{
	if (_row != second->_row || _col != second->_col)
	{
		return;
	}

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			if (second->_matrix[i][j] != 0)
			{
				_matrix[i][j] += second->_matrix[i][j];
			}
		}
	}
}
void matrix::subtractMatrix(matrix* second)
{
	if (_row != second->_row || _col != second->_col)
	{
		return;
	}

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			if (second->_matrix[i][j] != 0)
			{
				_matrix[i][j] -= second->_matrix[i][j];
			}
		}
	}
}
void matrix::multiplyMatrix(matrix* second)
{
	if (_col != second->_row)
	{
		return;
	}

	double** temp_matrix = new double* [_row];

	for (int t = 0; t < _row; t++)
	{
		temp_matrix[t] = new double[second->_col];
	}

	for (int i = 0; i < _row; i++)
	{
		for (int k = 0; k < _row; k++)
		{
			double sum = 0;

			for (int j = 0; j < _col; j++)
			{
				if (_matrix[i][j] != 0 && second->_matrix[j][k] != 0)
				{
					sum += _matrix[i][j] * second->_matrix[j][k];
				}
			}

			temp_matrix[i][k] = sum;
		}
	}

	free((void*)_matrix);

	_matrix = new double* [_row];

	_col = second->_col;

	for (int t = 0; t < _row; t++)
	{
		_matrix[t] = new double[_col];
	}

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			_matrix[i][j] = temp_matrix[i][j];
		}
	}
}
void matrix::multiplyScalar(double k)
{
	if (k == 1)
		return;

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			_matrix[i][j] *= k;
		}
	}
}

matrix matrix::TransPosedMatrix()
{
	matrix newm = new matrix(_col, _row);

	for (int j = 0; j < _col; j++)
	{
		for (int i = 0; i < _row; i++)
		{
			newm._matrix[j][i] = _matrix[i][j];
		}
	}

	return newm;
}
matrix matrix::AddedMatrix(matrix* second)
{
	if (_row != second->_row || _col != second->_col)
	{
		return NULL;
	}

	matrix newm = new matrix(this);

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			if (second->_matrix[i][j] != 0)
			{
				newm._matrix[i][j] += second->_matrix[i][j];
			}
		}
	}

	return newm;
}
matrix matrix::SubtractedMatrix(matrix* second)
{
	if (_row != second->_row || _col != second->_col)
	{
		return NULL;
	}

	matrix newm = new matrix(this);

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			if (second->_matrix[i][j] != 0)
			{
				newm._matrix[i][j] -= second->_matrix[i][j];
			}
		}
	}

	return newm;
}
matrix matrix::MultipledMatrix(matrix* second)
{
	if (_col != second->_row)
	{
		return NULL;
	}

	matrix new_matrix = new matrix(_row, second->_col);

	for (int i = 0; i < _row; i++)
	{
		for (int k = 0; k < _row; k++)
		{
			double sum = 0;

			for (int j = 0; j < _col; j++)
			{
				sum += _matrix[i][j] * second->_matrix[j][k];
			}

			new_matrix.setValue(i, k, sum);
		}
	}

	return new_matrix;
}
matrix matrix::MinorMatrix(int row, int col)
{
	matrix src = new matrix(_row - 1, _col - 1);

	double x = 0, y;

	for (int i = 0; i < _row; i++)
	{
		if (i == row)
		{
			x = 1;
			continue;
		}

		y = 0;

		for (int j = 0; j < _col; j++)
		{
			if (j == col)
			{
				y = 1;
			}
			else
			{
				src._matrix[x == 1 ? i - 1 : i][y == 1 ? j - 1 : j] = _matrix[i][j];
			}
		}
	}

	return src;
}
matrix matrix::AdjacentMatrix()
{
	matrix newm = new matrix(_row, _col);

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			newm.setValue(i, j, MinorMatrix(i, j).calculateDeterminant() * ((i + j) % 2 == 0 ? 1 : -1));
		}
	}

	newm.transPose();

	return newm;
}
matrix matrix::InverseMatrix()
{
	calculateDeterminant();

	matrix newm = AdjacentMatrix();

	newm.multiplyScalar(1 / determinant);

	return newm;
}

double matrix::calculateSarrus()
{
	if (_row != _col || _row > 3)
	{
		return INT32_MIN;
	}

	if (_row < 3)
	{
		return determinant = (_row == 1 ? _matrix[0][0] : (_matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0]));
	}

	double det = 0, prod;

	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < 3; i++)
		{
			prod = 1;

			for (int j = 0; j < 3; j++)
			{
				prod *= _matrix[(i + (k == 0 ? j : 2 - j)) % 3][j];
			}

			det += prod * (k == 0 ? 1 : -1);
		}
	}

	return determinant = det;
}
double matrix::calculateDeterminant()
{
	if (_row != _col)
	{
		return INT32_MIN;
	}

	if (determinant != INT32_MIN)
	{
		return determinant;
	}

	if (_row < 4 && _col < 4)
	{
		return calculateSarrus();
	}

	double det = 0;

	for (int i = 0; i < _row; i++)
	{
		matrix newm = MinorMatrix(i, 0);

		det += _matrix[i][0] * newm.calculateDeterminant() * (i % 2 == 0 ? 1 : -1);
	}

	return determinant = det;
}

matrix matrix::operator + (matrix& source)
{
	return AddedMatrix(&source);
}
matrix matrix::operator - (matrix& source)
{
	return SubtractedMatrix(&source);
}
matrix matrix::operator * (matrix& source)
{
	return MultipledMatrix(&source);
}