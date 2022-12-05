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

	_matrix = new int* [_row];

	for (int i = 0; i < _row; i++)
	{
		_matrix[i] = new int[_col];
	}
}
matrix::matrix(matrix* source)
{
	srand(time(NULL));

	_row = source->_row;
	_col = source->_col;

	_matrix = new int* [_row];

	for (int i = 0; i < _row; i++)
	{
		_matrix[i] = new int[_col];
	}

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			_matrix[i][j] = source->_matrix[i][j];
		}
	}
}
matrix::~matrix()
{

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

void matrix::setValue(int row, int col, int value)
{
	_matrix[row][col] = value;
}
void matrix::setRand(int row, int col, int max)
{
	_matrix[row][col] = rand() % ++max;
}
void matrix::fillValue(int value)
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
void matrix::transPose()
{
	int** temp_matrix = new int* [_col];

	for (int k = 0; k < _col; k++)
	{
		temp_matrix[k] = new int[_row];
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
			if (_matrix[i][j] != 0 && second->_matrix[i][j] != 0)
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
			if (_matrix[i][j] != 0 && second->_matrix[i][j] != 0)
			{
				_matrix[i][j] -= second->_matrix[i][j];
			}
		}
	}
}
void matrix::multiplyScalar(int k)
{
	if (k == 1)
		return;

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; i < _col; j++)
		{
			_matrix[i][j] *= k;
		}
	}
}
void matrix::multiplyMatrix(matrix* second)
{
	if (_col != second->_row)
	{
		return;
	}

	int** temp_matrix = new int* [_row];

	for (int t = 0; t < _row; t++)
	{
		temp_matrix[t] = new int[second->_col];
	}

	for (int i = 0; i < _row; i++)
	{
		for (int k = 0; k < _row; k++)
		{
			int sum = 0;

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

	_matrix = new int* [_row];

	_col = second->_col;

	for (int t = 0; t < _row; t++)
	{
		_matrix[t] = new int[_col];
	}

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			_matrix[i][j] = temp_matrix[i][j];
		}
	}
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
			if (newm._matrix[i][j] != 0 && second->_matrix[i][j] != 0)
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
			if (newm._matrix[i][j] != 0 && second->_matrix[i][j] != 0)
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
			int sum = 0;

			for (int j = 0; j < _col; j++)
			{
				sum += _matrix[i][j] * second->_matrix[j][k];
			}

			new_matrix.setValue(i, k, sum);
		}
	}

	return new_matrix;
}
matrix matrix::Minor(matrix* source, int row, int col)
{
	matrix src = new matrix(source->_row - 1, source->_col - 1);

	int x = 0, y;

	for (int i = 0; i < source->_row; i++)
	{
		if (i == row)
		{
			x = 1;
			continue;
		}

		y = 0;

		for (int j = 0; j < source->_col; j++)
		{
			if (j == col)
			{
				y = 1;
			}
			else
			{
				src._matrix[x == 1 ? i - 1 : i][y == 1 ? j - 1 : j] = source->_matrix[i][j];
			}
		}
	}

	return src;
}
matrix matrix::Adjacent(matrix* source)
{
	matrix newm = new matrix(source->_row, source->_col);

	for (int i = 0; i < source->_row; i++)
	{
		for (int j = 0; j < source->_col; j++)
		{
			matrix temp = source->Minor(source, i, j);

			newm.setValue(i, j, temp.calculateDeterminant(&temp) * ((i + j) % 2 == 0 ? 1 : -1));
		}
	}

	newm.transPose();

	return newm;
}

int matrix::calculateSarrus()
{
	if (_row != _col || _row > 3)
	{
		return INT32_MIN;
	}

	if (_row < 3)
	{
		return _row == 1 ? _matrix[0][0] : (_matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0]);
	}

	int det = 0, prod;

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

	return det;
}
int matrix::calculateDeterminant(matrix* source)
{
	if (source->_row != source->_col)
	{
		return INT32_MIN;
	}

	if (source->_row < 4 && source->_col < 4)
	{
		return source->calculateSarrus();
	}

	int det = 0;

	for (int i = 0; i < source->_row; i++)
	{
		matrix newm = Minor(source, i, 0);

		det += source->_matrix[i][0] * calculateDeterminant(&newm) * (i % 2 == 0 ? 1 : -1);
	}

	return det;
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
