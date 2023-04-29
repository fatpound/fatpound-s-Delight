#include <iostream>
#include <random>

#include "matrix.h"

using namespace std;

double matrix::get_rand(double first, double last)
{
    std::uniform_real_distribution<double> distribution(first, last);
    std::random_device rd;
    std::default_random_engine generator(rd());

    return distribution(generator);
}

matrix::matrix()
{

}
matrix::~matrix()
{

}
matrix::matrix(int row, int col)
{
    if (row < 1 || col < 1)
        return;

    _row = row;
    _col = col;

    for (int i = 0; i < row; i++)
    {
        _matrix.push_back(vector<double>(col));
    }
}
matrix::matrix(matrix& source)
{
    _row = source._row;
    _col = source._col;

    for (int i = 0; i < _row; i++)
    {
        _matrix.push_back(vector<double>(_col));
    }

    for (int i = 0; i < _row; i++)
    {
        for (int j = 0; j < _col; j++)
        {
            _matrix.at(i).at(j) = source._matrix.at(i).at(j);
        }
    }
}
matrix::matrix(double* arr, double length, int row, int col)
{
    if (row < 1 || col < 1)
        return;

    if (row * col != length)
        return;

    _row = row;
    _col = col;

    for (int i = 0; i < _row; i++)
    {
        _matrix.push_back(vector<double>(col));
    }

    int n = 0;

    for (int i = 0; i < _row; i++)
    {
        for (int j = 0; j < _col; j++)
        {
            _matrix.at(i).at(j) = arr[n];
            n++;
        }
    }
}
matrix::matrix(vector<double> vec, int row, int col)
{
    if (row < 1 || col < 1)
        return;

    if (row * col != vec.size())
        return;

    _row = row;
    _col = col;

    for (int i = 0; i < _row; i++)
    {
        _matrix.push_back(vector<double>(col));
    }

    int n = 0;

    for (int i = 0; i < _row; i++)
    {
        for (int j = 0; j < _col; j++)
        {
            _matrix.at(i).at(j) = vec.at(n);
            n++;
        }
    }
}

void matrix::printAll()
{
    for (int i = 0; i < _row; i++)
    {
        for (int j = 0; j < _col; j++)
        {
            cout << _matrix.at(i).at(j) << " ";
        }

        cout << '\n';
    }

    cout << '\n';
}
void matrix::printRow(int row)
{
    for (int i = 0; i < _col; i++)
    {
        cout << _matrix.at(row).at(i) << " ";
    }

    cout << '\n';
}
void matrix::printCol(int col)
{
    for (int i = 0; i < _row; i++)
    {
        cout << _matrix.at(i).at(col) << '\n';
    }
}

void matrix::toUnit()
{
    if (_row != _col)
        return;

    for (int i = 0; i < _row; i++)
    {
        for (int j = 0; j < _col; j++)
        {
            if (i == j && _matrix.at(i).at(j) != 1)
            {
                _matrix.at(i).at(j) = 1;
            }
            else if (_matrix.at(i).at(j) != 0)
            {
                _matrix.at(i).at(j) = 0;
            }
        }
    }
}
void matrix::setValue(int row, int col, int value)
{
    _matrix.at(row).at(col) = value;
}
void matrix::setValue(int row, int col, double value)
{
    _matrix.at(row).at(col) = value;
}
void matrix::setRand(int row, int col, int max)
{
    max++;
    _matrix.at(row).at(col) = (double)(int)get_rand(0, max);
}
void matrix::setRand(int row, int col, double max)
{
    max++;
    _matrix.at(row).at(col) = get_rand(0, max);
}
void matrix::fillValue(int value)
{
    for (int i = 0; i < _row; i++)
    {
        for (int j = 0; j < _col; j++)
        {
            _matrix.at(i).at(j) = value;
        }
    }
}
void matrix::fillValue(double value)
{
    for (int i = 0; i < _row; i++)
    {
        for (int j = 0; j < _col; j++)
        {
            _matrix.at(i).at(j) = value;
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
            _matrix.at(i).at(j) = (double)(int)get_rand(0, max);
        }
    }
}
void matrix::fillRand(double max)
{
    max++;

    for (int i = 0; i < _row; i++)
    {
        for (int j = 0; j < _col; j++)
        {
            _matrix.at(i).at(j) = get_rand(0, max);
        }
    }
}

void matrix::transPose()
{
    vector<vector<double>> temp_matrix;

    for (int k = 0; k < _col; k++)
    {
        temp_matrix.push_back(vector<double>(_row));
    }

    for (int j = 0; j < _col; j++)
    {
        for (int i = 0; i < _row; i++)
        {
            temp_matrix.at(j).at(i) = _matrix.at(i).at(j);
        }
    }

    _matrix = temp_matrix;
}
void matrix::addMatrix(matrix& second)
{
    if (_row != second._row || _col != second._col)
        return;

    for (int i = 0; i < _row; i++)
    {
        for (int j = 0; j < _col; j++)
        {
            if (second._matrix.at(i).at(j) != 0)
            {
                _matrix.at(i).at(j) += second._matrix.at(i).at(j);
            }
        }
    }
}
void matrix::subtractMatrix(matrix& second)
{
    if (_row != second._row || _col != second._col)
        return;

    for (int i = 0; i < _row; i++)
    {
        for (int j = 0; j < _col; j++)
        {
            if (second._matrix.at(i).at(j) != 0)
            {
                _matrix.at(i).at(j) -= second._matrix.at(i).at(j);
            }
        }
    }
}
void matrix::multiplyMatrix(matrix& second)
{
    if (_col != second._row)
        return;

    vector<vector<double>> temp_matrix;

    for (int i = 0; i < _row; i++)
    {
        temp_matrix.push_back(vector<double>(second._col));
    }

    for (int i = 0; i < _row; i++)
    {
        for (int k = 0; k < second._col; k++)
        {
            double sum = 0;

            for (int j = 0; j < _col; j++)
            {
                if (_matrix.at(i).at(j) != 0 && second._matrix.at(j).at(k) != 0)
                {
                    sum += _matrix.at(i).at(j) * second._matrix.at(j).at(k);
                }
            }

            temp_matrix.at(i).at(k) = sum;
        }
    }

    _matrix.clear();

    _col = second._col;

    for (int t = 0; t < _row; t++)
    {
        _matrix.push_back(vector<double>(_col));
    }

    for (int i = 0; i < _row; i++)
    {
        for (int j = 0; j < _col; j++)
        {
            _matrix.at(i).at(j) = temp_matrix.at(i).at(j);
        }
    }
}
void matrix::multiplyScalar(int k)
{
    if (k == 1)
        return;

    for (int i = 0; i < _row; i++)
    {
        for (int j = 0; j < _col; j++)
        {
            _matrix.at(i).at(j) *= (double)k;
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
            _matrix.at(i).at(j) *= k;
        }
    }
}

matrix matrix::TransPosedMatrix()
{
    matrix newm = matrix(_col, _row);

    for (int j = 0; j < _col; j++)
    {
        for (int i = 0; i < _row; i++)
        {
            newm._matrix.at(j).at(i) = _matrix.at(i).at(j);
        }
    }

    return newm;
}
matrix matrix::AddedMatrix(matrix& second)
{
    if (_row == second._row && _col == second._col)
    {
        matrix newm = matrix(*this);

        for (int i = 0; i < _row; i++)
        {
            for (int j = 0; j < _col; j++)
            {
                if (second._matrix.at(i).at(j) != 0)
                {
                    newm._matrix.at(i).at(j) += second._matrix.at(i).at(j);
                }
            }
        }

        return newm;
    }
}
matrix matrix::SubtractedMatrix(matrix& second)
{
    if (_row == second._row && _col == second._col)
    {
        matrix newm = matrix(*this);

        for (int i = 0; i < _row; i++)
        {
            for (int j = 0; j < _col; j++)
            {
                if (second._matrix.at(i).at(j) != 0)
                {
                    newm._matrix.at(i).at(j) -= second._matrix.at(i).at(j);
                }
            }
        }

        return newm;
    }
}
matrix matrix::MultipledMatrix(matrix& second)
{
    if (_col == second._row)
    {
        matrix new_matrix = matrix(_row, second._col);

        for (int i = 0; i < _row; i++)
        {
            for (int k = 0; k < second._col; k++)
            {
                double sum = 0;

                for (int j = 0; j < _col; j++)
                {
                    sum += _matrix.at(i).at(j) * second._matrix.at(j).at(k);
                }

                new_matrix.setValue(i, k, sum);
            }
        }

        return new_matrix;
    }
}
matrix matrix::MinorMatrix(int row, int col)
{
    matrix src = matrix(_row - 1, _col - 1);

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
                src._matrix.at(x == 1 ? i - 1 : i).at(y == 1 ? j - 1 : j) = _matrix.at(i).at(j);
            }
        }
    }

    return src;
}
matrix matrix::AdjacentMatrix()
{
    matrix newm = matrix(_row, _col);

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

    if (this->getDeterminant() != 0)
    {
        matrix newm = AdjacentMatrix();

        newm.multiplyScalar(1 / this->getDeterminant());

        return newm;
    }
}
// kofaktörü yap
double matrix::calculateSarrus()
{
    double det = 0;

    for (int k = 0; k < 2; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            double prod = 1;

            for (int j = 0; j < 3; j++)
            {
                prod *= this->_matrix.at((i + (k == 0 ? j : 2 - j)) % 3).at(j);
            }

            det += prod * (k == 0 ? 1 : -1);
        }
    }

    return det;
}
double matrix::calculateDeterminant()
{
    double det = 0;

    for (int i = 0; i < _row; i++)
    {
        matrix newm = MinorMatrix(i, 0);

        det += _matrix.at(i).at(0) * newm.calculateDeterminant() * (i % 2 == 0 ? 1 : -1);
    }

    return det;
}

double matrix::getSarrus()
{
    if (_row != _col || _row > 3)
        return INT32_MIN;

    if (_row < 3)
    {
        return (_row == 1 ? _matrix.at(0).at(0) : (_matrix.at(0).at(0) * _matrix.at(1).at(1) - _matrix.at(0).at(1) * _matrix.at(1).at(0)));
    }

    return calculateSarrus();
}
double matrix::getDeterminant()
{
    if (_row != _col)
        return INT32_MIN;

    if (_row < 4 && _col < 4)
        return getSarrus();

    return calculateDeterminant();
}

matrix matrix::operator + (matrix& source)
{
    return AddedMatrix(source);
}
matrix matrix::operator - (matrix& source)
{
    return SubtractedMatrix(source);
}
matrix matrix::operator * (matrix& source)
{
    return MultipledMatrix(source);
}
