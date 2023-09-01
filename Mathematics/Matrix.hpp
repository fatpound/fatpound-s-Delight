#pragma once

#include "fatpound.hpp"

namespace fatpound::math
{
    template <typename T>
    class Matrix
    {
    private:
        T* matrix = nullptr;

        std::size_t rowCount = 0;
        std::size_t columnCount = 0;

        std::int64_t determinant = 0;

        bool determinantInitialized = false;


        T GetRand(T first, T last) const;

        void CalculateDeterminant();


    protected:


    public:
        Matrix() = delete;
        Matrix(const std::int64_t row, const std::int64_t col);
        Matrix(const std::vector<T>& vec, const std::int64_t row, const std::int64_t col);
        ~Matrix();
        Matrix(const Matrix<T>& src);
        Matrix& operator = (const Matrix<T>& src);

        void PrintAll() const;
        void PrintRow(const std::int64_t row) const;
        void PrintColumn(const std::int64_t col) const;

        void ConvertToUnit();
        void SetValue(const std::int64_t row, const std::int64_t col, const T value);
        void SetRand(const std::int64_t row, const std::int64_t col, const std::int64_t max_excluded);
        void FillValue(const T value);
        void FillRand(const T max_excluded);

        void Transpose();
        void Add(const Matrix<T>& second);
        void Subtract(const Matrix<T>& second);
        void Multiply(const Matrix<T>& second);
        void Multiply(const T k);

        T GetDeterminant();

        Matrix<T> AddedMatrix(const Matrix<T>& src) const;
        Matrix<T> SubtractedMatrix(const Matrix<T>& src) const;
        Matrix<T> MultipliedMatrix(const Matrix<T>& src) const;
        Matrix<T> TransposedMatrix() const;
        Matrix<T> MinorMatrix(const std::int64_t row, const std::int64_t col) const;
        Matrix<T> AdjacentMatrix() const;
        Matrix<T> InverseMatrix() const;

        Matrix<T>& operator += (const Matrix<T>& src);
        Matrix<T>& operator -= (const Matrix<T>& src);
        Matrix<T>& operator *= (const Matrix<T>& src);
    };


    template <typename T> Matrix<T>::Matrix(const std::int64_t row, const std::int64_t col)
    {
        if (row < 1 || col < 1)
            return;

        rowCount = row;
        columnCount = col;

        matrix = new T[row * col];
    }
    template <typename T> Matrix<T>::Matrix(const std::vector<T>& vec, const std::int64_t row, const std::int64_t col)
    {
        if (row < 1 || col < 1)
            return;

        if (row * col != vec.size())
            return;

        rowCount = row;
        columnCount = col;

        matrix = new T[row * col];

        std::size_t n = 0;

        for (std::size_t i = 0; i < rowCount; i++)
        {
            for (std::size_t j = 0; j < columnCount; j++)
            {
                matrix[i][j] = vec[n];
                n++;
            }
        }
    }
    template <typename T> Matrix<T>::~Matrix()
    {
        delete [] matrix;
        matrix = nullptr;
    }
    template <typename T> Matrix<T>::Matrix(const Matrix<T>& src)
    {
        if (src.rowCount < 1 || src.columnCount < 1)
            return;

        rowCount = src.rowCount;
        columnCount = src.columnCount;

        matrix = new T[rowCount * columnCount];

        for (std::size_t i = 0; i < rowCount; i++)
        {
            for (std::size_t j = 0; j < columnCount; j++)
            {
                matrix[i * columnCount + j] = src.matrix[i * columnCount + j];
            }
        }
    }
    template <typename T> Matrix<T>& Matrix<T>::operator = (const Matrix<T>& src)
    {
        if ( ! (src.rowCount < 1 || src.columnCount < 1) && (*this != src))
        {
            if (matrix != nullptr)
            {
                delete [] matrix;
                matrix = nullptr;

                rowCount = 0;
                columnCount = 0;
            }

            rowCount = src.rowCount;
            columnCount = src.columnCount;

            matrix = new T[rowCount * columnCount];

            for (std::size_t i = 0; i < rowCount; i++)
            {
                for (std::size_t j = 0; j < columnCount; j++)
                {
                    matrix[i * columnCount + j] = src.matrix[i * columnCount + j];
                }
            }
        }

        return *this;
    }

    template <typename T> void Matrix<T>::PrintAll() const
    {
        for (std::size_t i = 0; i < rowCount; i++)
        {
            PrintRow(i);
        }

        std::cout << '\n';
    }
    template <typename T> void Matrix<T>::PrintRow(const std::int64_t row) const
    {
        for (std::size_t i = 0; i < columnCount; i++)
        {
            std::cout << matrix[row * columnCount + i] << " ";
        }

        std::cout << '\n';
    }
    template <typename T> void Matrix<T>::PrintColumn(const std::int64_t col) const
    {
        for (std::size_t j = 0; j < rowCount; j++)
        {
            std::cout << matrix[j * rowCount + col] << '\n';
        }
    }

    template <typename T> void Matrix<T>::ConvertToUnit()
    {
        if (rowCount != columnCount)
            return;

        if (rowCount < 1 || columnCount < 1)
            return;

        for (std::size_t i = 0; i < rowCount; i++)
        {
            for (std::size_t j = 0; j < columnCount; j++)
            {
                matrix[i * columnCount + j] = (i == j ? 1 : 0);
            }
        }
    }
    template <typename T> void Matrix<T>::SetValue(const std::int64_t row, const std::int64_t col, const T value)
    {
        matrix[row * columnCount + col] = value;
    }
    template <typename T> void Matrix<T>::SetRand(const std::int64_t row, const std::int64_t col, const std::int64_t max_excluded)
    {
        matrix[row * columnCount + col] = GetRand(0, max_excluded);
    }
    template <typename T> void Matrix<T>::FillValue(const T value)
    {
        for (std::size_t i = 0; i < rowCount; i++)
        {
            for (std::size_t j = 0; j < columnCount; j++)
            {
                matrix[i * columnCount + j] = value;
            }
        }
    }
    template <typename T> void Matrix<T>::FillRand(const T max_excluded)
    {
        for (std::size_t i = 0; i < rowCount; i++)
        {
            for (std::size_t j = 0; j < columnCount; j++)
            {
                matrix[i * columnCount + j] = GetRand(0, max_excluded);
            }
        }
    }

    template <typename T> void Matrix<T>::Transpose()
    {
        Matrix<T> copy(*this);

        for (std::size_t i = 0; i < rowCount; i++)
        {
            for (std::size_t j = 0; j < columnCount; j++)
            {
                matrix[i * columnCount + j] = copy.matrix[j * rowCount + i];
            }
        }

        std::swap(rowCount, columnCount);
    }
    template <typename T> void Matrix<T>::Add(const Matrix<T>& second)
    {
        if (rowCount != second.rowCount || columnCount != second.columnCount)
            return;

        for (std::size_t i = 0; i < rowCount; i++)
        {
            for (std::size_t j = 0; j < columnCount; j++)
            {
                if (second.matrix[i * columnCount + j] != 0)
                {
                    matrix[i * columnCount + j] += second.matrix[i * columnCount + j];
                }
            }
        }
    }
    template <typename T> void Matrix<T>::Subtract(const Matrix<T>& second)
    {
        if (rowCount != second.rowCount || columnCount != second.columnCount)
            return;

        for (std::size_t i = 0; i < rowCount; i++)
        {
            for (std::size_t j = 0; j < columnCount; j++)
            {
                if (second.matrix[i * columnCount + j] != 0)
                {
                    matrix[i * columnCount + j] -= second.matrix[i * columnCount + j];
                }
            }
        }
    }
    template <typename T> void Matrix<T>::Multiply(const Matrix<T>& second)
    {
        if (columnCount != second.rowCount)
            return;

        Matrix<T> temp(rowCount, second.columnCount);

        for (std::size_t i = 0; i < rowCount; i++)
        {
            for (std::size_t k = 0; k < second.columnCount; k++)
            {
                T sum = 0;

                for (std::size_t j = 0; j < columnCount; j++)
                {
                    if (matrix[i * columnCount + j] != 0 && second.matrix[j * second.columnCount + k] != 0)
                    {
                        sum += matrix[i * columnCount + j] * second.matrix[j * second.columnCount + k];
                    }
                }

                temp.matrix[i * temp.columnCount + k] = sum;
            }
        }

        columnCount = second.columnCount;

        for (std::size_t i = 0; i < rowCount; i++)
        {
            for (std::size_t j = 0; j < columnCount; j++)
            {
                matrix[i * columnCount + j] = temp.matrix[i * columnCount + j];
            }
        }
    }
    template <typename T> void Matrix<T>::Multiply(const T k)
    {
        if (k == 1)
            return;

        for (std::size_t i = 0; i < rowCount; i++)
        {
            for (std::size_t j = 0; j < columnCount; j++)
            {
                matrix[i * columnCount + j] *= k;
            }
        }
    }
    
    template <typename T> Matrix<T> Matrix<T>::AddedMatrix(const Matrix<T>& src) const
    {
        Matrix<T> newm(*this);

        newm.Add(src);

        return newm;
    }
    template <typename T> Matrix<T> Matrix<T>::SubtractedMatrix(const Matrix<T>& src) const
    {
        Matrix<T> newm(*this);

        newm.Subtract(src);

        return newm;
    }
    template <typename T> Matrix<T> Matrix<T>::MultipliedMatrix(const Matrix<T>& src) const
    {
        Matrix<T> newm(*this);

        newm.Multiply(src);

        return newm;
    }
    template <typename T> Matrix<T> Matrix<T>::TransposedMatrix() const
    {
        Matrix<T> newm(columnCount, rowCount);

        for (std::size_t j = 0; j < columnCount; j++)
        {
            for (std::size_t i = 0; i < rowCount; i++)
            {
                newm.matrix[j * newm.columnCount + i] = matrix[i * columnCount + j];
            }
        }

        return newm;
    }
    template <typename T> Matrix<T> Matrix<T>::MinorMatrix(const std::int64_t row, const std::int64_t col) const
    {
        Matrix<T> newm(rowCount - 1, columnCount - 1);

        T x = 0;
        T y ;

        for (std::size_t i = 0; i < rowCount; i++)
        {
            if (i == row)
            {
                x = 1;
                continue;
            }

            y = 0;

            for (std::size_t j = 0; j < columnCount; j++)
            {
                if (j == col)
                {
                    y = 1;
                }
                else
                {
                    newm.matrix[(x == 1 ? i - 1 : i) * newm.columnCount + (y == 1 ? j - 1 : j)] = matrix[i * columnCount + j];
                }
            }
        }

        return newm;
    }
    template <typename T> Matrix<T> Matrix<T>::AdjacentMatrix() const
    {
        Matrix<T> newm(rowCount, columnCount);

        for (std::size_t i = 0; i < rowCount; i++)
        {
            for (std::size_t j = 0; j < columnCount; j++)
            {
                newm.SetValue(i, j, MinorMatrix(i, j).GetDeterminant() * ((i + j) % 2 == 0 ? 1 : -1));
            }
        }

        newm.Transpose();

        return newm;
    }
    template <typename T> Matrix<T> Matrix<T>::InverseMatrix() const
    {
        if (determinantInitialized && determinant != 0)
        {
            Matrix<T> newm = AdjacentMatrix();

            newm.Multiply(1 / GetDeterminant());

            return newm;
        }

        return Matrix<T>();
    }
    
    template <typename T> void Matrix<T>::CalculateDeterminant()
    {
        if (rowCount == columnCount && rowCount > 0)
        {
            switch (rowCount)
            {
            case 1:
            {
                determinant = matrix[0];
            }
            break;

            case 2:
            {
                determinant = (matrix[0] * matrix[columnCount + 1] - matrix[1] * matrix[columnCount]);
            }
            break;

            case 3:
            {
                for (std::size_t k = 0; k < 2; k++)
                {
                    for (std::size_t i = 0; i < 3; i++)
                    {
                        T prod = 1;

                        for (std::size_t j = 0; j < 3; j++)
                        {
                            prod *= matrix[((i + (k == 0 ? j : 2 - j)) % 3) * columnCount + j];
                        }

                        determinant += prod * (k == 0 ? 1 : -1);
                    }
                }
            }
            break;

            default:
            {
                for (std::size_t i = 0; i < rowCount; i++)
                {
                    Matrix* newm = MinorMatrix(i, 0);

                    determinant += matrix[i * columnCount] * newm->GetDeterminant() * (i % 2 == 0 ? 1 : -1);

                    delete newm;
                }
            }
            break;
            }
        }
    }

    template <typename T> T Matrix<T>::GetRand(T first, T last) const
    {
        std::uniform_real_distribution<double> distribution(first, last);
        std::random_device rd;
        std::default_random_engine rng(rd());

        return distribution(rng);
    }
    template <typename T> T Matrix<T>::GetDeterminant()
    {
        if ( ! determinantInitialized )
        {
            CalculateDeterminant();

            determinantInitialized = true;
        }

        return determinant;
    }
    
    template <typename T> Matrix<T>& Matrix<T>::operator += (const Matrix<T>& src)
    {
        Add(src);

        return *this;
    }
    template <typename T> Matrix<T>& Matrix<T>::operator -= (const Matrix<T>& src)
    {
        Subtract(src);

        return *this;
    }
    template <typename T> Matrix<T>& Matrix<T>::operator *= (const Matrix<T>& src)
    {
        Multiply(src);

        return *this;
    }
}