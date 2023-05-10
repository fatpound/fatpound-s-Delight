#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <array>

template <typename T>
class matrix
{
private:
    T calculateSarrus();
    T calculateDeterminant();
    T get_rand(T first, T last);


public:
    std::vector<std::vector<T>> matris;

    int row_count = 0;
    int col_count = 0;

    matrix();
    ~matrix();
    matrix(int row, int col);
    matrix(matrix<T>& source);
    matrix(T* arr, T length, int row, int col);
    matrix(std::vector<T> vec, int row, int col);
    matrix(std::vector<std::vector<T>> vec);

    void printAll();
    void printRow(int row);
    void printCol(int col);

    void toUnit();
    void setValue(int row, int col, int value);
    void setValue(int row, int col, T value);
    void setRand(int row, int col, int max);
    void setRand(int row, int col, T max);
    void fillValue(int value);
    void fillValue(T value);
    void fillRand(int max);
    void fillRand(T max);
    
    void transPose();
    void addMatrix(matrix<T>& second);
    void subtractMatrix(matrix<T>& second);
    void multiplyMatrix(matrix<T>& second);
    void multiplyScalar(int k);
    void multiplyScalar(T k);
    
    matrix<T> TransPosedMatrix();
    matrix<T> AddedMatrix(matrix<T>& second);
    matrix<T> SubtractedMatrix(matrix<T>& second);
    matrix<T> MultipledMatrix(matrix<T>& second);
    matrix<T> MinorMatrix(int row, int col);
    matrix<T> AdjacentMatrix();
    matrix<T> InverseMatrix();
    
    T getSarrus();
    T getDeterminant();
    
    matrix<T>& operator + (matrix<T>& source);
    matrix<T>& operator - (matrix<T>& source);
    matrix<T>& operator * (matrix<T>& source);
};

template <typename T> T matrix<T>::get_rand(T first, T last)
{
    std::uniform_real_distribution<T> distribution(first, last);
    std::random_device rd;
    std::default_random_engine generator(rd());

    return distribution(generator);
}

template <typename T> matrix<T>::matrix()
{

}
template <typename T> matrix<T>::~matrix()
{

}
template <typename T> matrix<T>::matrix(int row, int col)
{
    if (row < 1 || col < 1)
        return;

    this->row_count = row;
    this->col_count = col;

    for (int i = 0; i < row; i++)
    {
        this->matris.push_back(std::vector<T>(col));
    }
}
template <typename T> matrix<T>::matrix(matrix<T>& source)
{
    this->row_count = source.row_count;
    this->col_count = source.col_count;

    for (int i = 0; i < this->row_count; i++)
    {
        this->matris.push_back(std::vector<T>(this->col_count));
    }

    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            this->matris.at(i).at(j) = source.matris.at(i).at(j);
        }
    }
}
template <typename T> matrix<T>::matrix(T* arr, T length, int row, int col)
{
    if (row < 1 || col < 1)
        return;

    if (row * col != length)
        return;

    this->row_count = row;
    this->col_count = col;

    for (int i = 0; i < this->row_count; i++)
    {
        this->matris.push_back(std::vector<T>(col));
    }

    int n = 0;

    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            this->matris.at(i).at(j) = arr[n];
            n++;
        }
    }
}
template <typename T> matrix<T>::matrix(std::vector<T> vec, int row, int col)
{
    if (row < 1 || col < 1)
        return;

    if (row * col != vec.size())
        return;

    this->row_count = row;
    this->col_count = col;

    for (int i = 0; i < this->row_count; i++)
    {
        this->matris.push_back(std::vector<T>(col));
    }

    int n = 0;

    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            this->matris.at(i).at(j) = vec.at(n);
            n++;
        }
    }
}
template <typename T> matrix<T>::matrix(std::vector<std::vector<T>> vec)
{
    this->matris = std::vector<std::vector<T>>(vec);
}

template <typename T> void matrix<T>::printAll()
{
    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            std::cout << this->matris.at(i).at(j) << " ";
        }

        std::cout << '\n';
    }

    std::cout << '\n';
}
template <typename T> void matrix<T>::printRow(int row)
{
    for (int i = 0; i < this->col_count; i++)
    {
        std::cout << this->matris.at(row).at(i) << " ";
    }

    std::cout << '\n';
}
template <typename T> void matrix<T>::printCol(int col)
{
    for (int i = 0; i < this->row_count; i++)
    {
        std::cout << this->matris.at(i).at(col) << '\n';
    }
}

template <typename T> void matrix<T>::toUnit()
{
    if (this->row_count != this->col_count)
        return;

    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            if (i == j && this->matris.at(i).at(j) != 1)
            {
                this->matris.at(i).at(j) = 1;
            }
            else if (this->matris.at(i).at(j) != 0)
            {
                this->matris.at(i).at(j) = 0;
            }
        }
    }
}
template <typename T> void matrix<T>::setValue(int row, int col, int value)
{
    this->matris.at(row).at(col) = value;
}
template <typename T> void matrix<T>::setValue(int row, int col, T value)
{
    this->matris.at(row).at(col) = value;
}
template <typename T> void matrix<T>::setRand(int row, int col, int max)
{
    max++;
    this->matris.at(row).at(col) = (T)(int)get_rand(0, max);
}
template <typename T> void matrix<T>::setRand(int row, int col, T max)
{
    max++;
    this->matris.at(row).at(col) = get_rand(0, max);
}
template <typename T> void matrix<T>::fillValue(int value)
{
    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            this->matris.at(i).at(j) = value;
        }
    }
}
template <typename T> void matrix<T>::fillValue(T value)
{
    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            this->matris.at(i).at(j) = value;
        }
    }
}
template <typename T> void matrix<T>::fillRand(int max)
{
    max++;

    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            this->matris.at(i).at(j) = (T)(int)get_rand(0, max);
        }
    }
}
template <typename T> void matrix<T>::fillRand(T max)
{
    max++;

    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            this->matris.at(i).at(j) = get_rand(0, max);
        }
    }
}

template <typename T> void matrix<T>::transPose()
{
    std::vector<std::vector<T>> tempmatris;

    for (int k = 0; k < this->col_count; k++)
    {
        tempmatris.push_back(std::vector<T>(this->row_count));
    }

    for (int j = 0; j < this->col_count; j++)
    {
        for (int i = 0; i < this->row_count; i++)
        {
            tempmatris.at(j).at(i) = this->matris.at(i).at(j);
        }
    }

    matris = tempmatris;
}
template <typename T> void matrix<T>::addMatrix(matrix<T>& second)
{
    if (this->row_count != second.row_count || this->col_count != second.col_count)
        return;

    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            if (second.matris.at(i).at(j) != 0)
            {
                this->matris.at(i).at(j) += second.matris.at(i).at(j);
            }
        }
    }
}
template <typename T> void matrix<T>::subtractMatrix(matrix<T>& second)
{
    if (this->row_count != second.row_count || this->col_count != second.col_count)
        return;

    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            if (second.matris.at(i).at(j) != 0)
            {
                this->matris.at(i).at(j) -= second.matris.at(i).at(j);
            }
        }
    }
}
template <typename T> void matrix<T>::multiplyMatrix(matrix<T>& second)
{
    if (this->col_count != second.row_count)
        return;

    std::vector<std::vector<T>> tempmatris;

    for (int i = 0; i < this->row_count; i++)
    {
        tempmatris.push_back(std::vector<T>(second.col_count));
    }

    for (int i = 0; i < this->row_count; i++)
    {
        for (int k = 0; k < second.col_count; k++)
        {
            T sum = 0;

            for (int j = 0; j < this->col_count; j++)
            {
                if (this->matris.at(i).at(j) != 0 && second.matris.at(j).at(k) != 0)
                {
                    sum += this->matris.at(i).at(j) * second.matris.at(j).at(k);
                }
            }

            tempmatris.at(i).at(k) = sum;
        }
    }

    this->matris.clear();

    this->col_count = second.col_count;

    for (int t = 0; t < this->row_count; t++)
    {
        this->matris.push_back(std::vector<T>(this->col_count));
    }

    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            this->matris.at(i).at(j) = tempmatris.at(i).at(j);
        }
    }
}
template <typename T> void matrix<T>::multiplyScalar(int k)
{
    if (k == 1)
        return;

    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            this->matris.at(i).at(j) *= (T)k;
        }
    }
}
template <typename T> void matrix<T>::multiplyScalar(T k)
{
    if (k == 1)
        return;

    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            this->matris.at(i).at(j) *= k;
        }
    }
}

template <typename T> matrix<T> matrix<T>::TransPosedMatrix()
{
    matrix newm = matrix(this->col_count, this->row_count);

    for (int j = 0; j < this->col_count; j++)
    {
        for (int i = 0; i < this->row_count; i++)
        {
            newm.matris.at(j).at(i) = this->matris.at(i).at(j);
        }
    }

    return newm;
}
template <typename T> matrix<T> matrix<T>::AddedMatrix(matrix<T>& second)
{
    if (this->row_count == second.row_count && this->col_count == second.col_count)
    {
        matrix newm = matrix(*this);

        for (int i = 0; i < this->row_count; i++)
        {
            for (int j = 0; j < this->col_count; j++)
            {
                if (second.matris.at(i).at(j) != 0)
                {
                    newm.matris.at(i).at(j) += second.matris.at(i).at(j);
                }
            }
        }

        return newm;
    }
}
template <typename T> matrix<T> matrix<T>::SubtractedMatrix(matrix<T>& second)
{
    if (this->row_count == second.row_count && this->col_count == second.col_count)
    {
        matrix newm = matrix(*this);

        for (int i = 0; i < this->row_count; i++)
        {
            for (int j = 0; j < this->col_count; j++)
            {
                if (second.matris.at(i).at(j) != 0)
                {
                    newm.matris.at(i).at(j) -= second.matris.at(i).at(j);
                }
            }
        }

        return newm;
    }
}
template <typename T> matrix<T> matrix<T>::MultipledMatrix(matrix<T>& second)
{
    if (this->col_count == second.row_count)
    {
        matrix newmatris = matrix(this->row_count, second.col_count);

        for (int i = 0; i < this->row_count; i++)
        {
            for (int k = 0; k < second.col_count; k++)
            {
                T sum = 0;

                for (int j = 0; j < this->col_count; j++)
                {
                    sum += this->matris.at(i).at(j) * second.matris.at(j).at(k);
                }

                newmatris.setValue(i, k, sum);
            }
        }

        return newmatris;
    }
}
template <typename T> matrix<T> matrix<T>::MinorMatrix(int row, int col)
{
    matrix src = matrix(this->row_count - 1, this->col_count - 1);

    T x = 0, y;

    for (int i = 0; i < this->row_count; i++)
    {
        if (i == row)
        {
            x = 1;
            continue;
        }

        y = 0;

        for (int j = 0; j < this->col_count; j++)
        {
            if (j == col)
            {
                y = 1;
            }
            else
            {
                src.matris.at(x == 1 ? i - 1 : i).at(y == 1 ? j - 1 : j) = this->matris.at(i).at(j);
            }
        }
    }

    return src;
}
template <typename T> matrix<T> matrix<T>::AdjacentMatrix()
{
    matrix newm = matrix(this->row_count, this->col_count);

    for (int i = 0; i < this->row_count; i++)
    {
        for (int j = 0; j < this->col_count; j++)
        {
            newm.setValue(i, j, MinorMatrix(i, j).calculateDeterminant() * ((i + j) % 2 == 0 ? 1 : -1));
        }
    }

    newm.transPose();

    return newm;
}
template <typename T> matrix<T> matrix<T>::InverseMatrix()
{
    calculateDeterminant();

    if (this->getDeterminant() != 0)
    {
        matrix newm = AdjacentMatrix();

        newm.multiplyScalar(1 / this->getDeterminant());

        return newm;
    }
}

template <typename T> T matrix<T>::calculateSarrus()
{
    T det = 0;

    for (int k = 0; k < 2; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            T prod = 1;

            for (int j = 0; j < 3; j++)
            {
                prod *= this->matris.at((i + (k == 0 ? j : 2 - j)) % 3).at(j);
            }

            det += prod * (k == 0 ? 1 : -1);
        }
    }

    return det;
}
template <typename T> T matrix<T>::calculateDeterminant()
{
    T det = 0;

    for (int i = 0; i < this->row_count; i++)
    {
        matrix newm = MinorMatrix(i, 0);

        det += this->matris.at(i).at(0) * newm.calculateDeterminant() * (i % 2 == 0 ? 1 : -1);
    }

    return det;
}

template <typename T> T matrix<T>::getSarrus()
{
    if (this->row_count != this->col_count || this->row_count > 3)
        return INT32_MIN;

    if (this->row_count < 3)
    {
        return (this->row_count == 1 ? this->matris.at(0).at(0) : (this->matris.at(0).at(0) * this->matris.at(1).at(1) - this->matris.at(0).at(1) * this->matris.at(1).at(0)));
    }

    return calculateSarrus();
}
template <typename T> T matrix<T>::getDeterminant()
{
    if (this->row_count != this->col_count)
        return INT32_MIN;

    if (this->row_count < 4 && this->col_count < 4)
        return getSarrus();

    return calculateDeterminant();
}

template <typename T> matrix<T>& matrix<T>::operator + (matrix<T>& source)
{
    return AddedMatrix(source);
}
template <typename T> matrix<T>& matrix<T>::operator - (matrix<T>& source)
{
    return SubtractedMatrix(source);
}
template <typename T> matrix<T>& matrix<T>::operator * (matrix<T>& source)
{
    return MultipledMatrix(source);
}