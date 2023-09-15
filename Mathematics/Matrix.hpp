#pragma once

#include "fatpound.hpp"

namespace fatpound::math
{
    template <typename T>
    class Matrix
    {
    private:
        std::unique_ptr<T[]> matrix = nullptr;

        size_t rowCount = 0;
        size_t colCount = 0;

        int64_t determinant = INT64_MIN;
        bool detInitialized = false;

        static T GetRand(T first, T last);
        void CalculateDeterminant();
        

        Matrix<T>* AddedMatrix(const Matrix<T>& src) const;
        Matrix<T>* SubtractedMatrix(const Matrix<T>& src) const;
        Matrix<T>* MultipliedMatrix(const Matrix<T>& src) const;
        Matrix<T>* TransposedMatrix() const;
        Matrix<T>* MinorMatrix(const int64_t row, const int64_t col) const;
        Matrix<T>* AdjacentMatrix() const;
        Matrix<T>* InverseMatrix() const;
        

    protected:


    public:
        Matrix() = default;
        ~Matrix() noexcept;
        Matrix(const Matrix<T>& src) noexcept;
        Matrix(Matrix<T>&& src) noexcept;
        Matrix& operator = (const Matrix<T>& src) noexcept;
        Matrix& operator = (Matrix<T>&& src) noexcept;

        Matrix(const int64_t row, const int64_t col);
        Matrix(const std::vector<T>& vec, const int64_t row, const int64_t col);

        void Print() const;
        void PrintRow(const int64_t row) const;
        void PrintColumn(const int64_t col) const;
        
        void SetValue(const int64_t row, const int64_t col, const T value);
        void SetRand(const int64_t row, const int64_t col, const int64_t max_excluded);
        void FillValue(const T value);
        void FillRand(const T max_excluded);

        void Transpose();
        void ConvertToUnit();
        void Add(const Matrix<T>& second);
        void Subtract(const Matrix<T>& second);
        void Multiply(const Matrix<T>& second);
        void Multiply(const T k);

        T GetValue(const int64_t row, const int64_t col) const;
        T GetDeterminant() const;
        
        Matrix<T>  operator ~  ();
        Matrix<T>  operator !  ();

        Matrix<T>  operator +  (const Matrix<T>& src);
        Matrix<T>  operator -  (const Matrix<T>& src);
        Matrix<T>  operator *  (const Matrix<T>& src);

        Matrix<T>& operator += (const Matrix<T>& src);
        Matrix<T>& operator -= (const Matrix<T>& src);
        Matrix<T>& operator *= (const Matrix<T>& src);
    };


    template <typename T> Matrix<T>::~Matrix() noexcept
    {

    }
    template <typename T> Matrix<T>::Matrix(const Matrix<T>& src) noexcept
    {
        if (src.matrix != nullptr)
        {
            rowCount = src.rowCount;
            colCount = src.colCount;

            determinant = src.determinant;
            detInitialized = src.detInitialized;

            matrix = std::make_unique<T[]>(rowCount * colCount);

            for (size_t i = 0; i < rowCount; i++)
            {
                for (size_t j = 0; j < colCount; j++)
                {
                    matrix[i * colCount + j] = src.matrix[i * colCount + j];
                }
            }

            CalculateDeterminant();
        }
    }
    template <typename T> Matrix<T>::Matrix(Matrix<T>&& src) noexcept
    {
        if (src.matrix != nullptr)
        {
            matrix = std::move(src.matrix);

            rowCount = std::move(src.rowCount);
            colCount = std::move(src.colCount);

            src.rowCount = 0;
            src.colCount = 0;

            determinant = std::move(src.determinant);
            detInitialized = std::move(src.detInitialized);

            src.determinant = INT64_MIN;
            src.detInitialized = false;
        }
    }
    template <typename T> Matrix<T>& Matrix<T>::operator = (const Matrix<T>& src) noexcept
    {
        if (this != std::addressof(src) && src.matrix != nullptr)
        {
            if (matrix != nullptr)
            {
                T* p = matrix.release();
                delete [] p;
            }

            rowCount = src.rowCount;
            colCount = src.colCount;

            determinant = src.determinant;
            detInitialized = src.detInitialized;

            matrix = std::make_unique<T[]>(rowCount * colCount);

            for (size_t i = 0; i < rowCount; i++)
            {
                for (size_t j = 0; j < colCount; j++)
                {
                    matrix[i * colCount + j] = src.matrix[i * colCount + j];
                }
            }

            CalculateDeterminant();
        }

        return *this;
    }
    template <typename T> Matrix<T>& Matrix<T>::operator = (Matrix<T>&& src) noexcept
    {
        if (this != std::addressof(src) && src.matrix != nullptr)
        {
            if (matrix != nullptr)
            {
                T* p = matrix.release();
                delete [] p;
            }

            matrix = std::move(src.matrix);

            rowCount = std::move(src.rowCount);
            colCount = std::move(src.colCount);

            src.rowCount = 0;
            src.colCount = 0;

            determinant = std::move(src.determinant);
            detInitialized = std::move(src.detInitialized);

            src.determinant = INT64_MIN;
            src.detInitialized = false;
        }

        return *this;
    }

    template <typename T> Matrix<T>::Matrix(const int64_t row, const int64_t col)
    {
        if (row < 1 || col < 1)
        {
            return;
        }

        rowCount = row;
        colCount = col;

        matrix = std::make_unique<T[]>(rowCount * colCount);
    }
    template <typename T> Matrix<T>::Matrix(const std::vector<T>& vec, const int64_t row, const int64_t col)
    {
        if (row < 1 || col < 1)
        {
            return;
        }

        if (row * col != vec.size())
        {
            return;
        }

        rowCount = row;
        colCount = col;

        matrix = std::make_unique<T[]>(rowCount * colCount);

        for (size_t i = 0; i < rowCount * colCount; i++)
        {
            matrix[i] = vec[i];
        }

        CalculateDeterminant();
    }

    template <typename T> void Matrix<T>::Print() const
    {
        for (size_t i = 0; i < rowCount; i++)
        {
            PrintRow(i);
        }

        std::cout << '\n';
    }
    template <typename T> void Matrix<T>::PrintRow(const int64_t row) const
    {
        for (size_t i = 0; i < colCount; i++)
        {
            std::cout << matrix[row * colCount + i] << " ";
        }

        std::cout << '\n';
    }
    template <typename T> void Matrix<T>::PrintColumn(const int64_t col) const
    {
        for (size_t j = 0; j < rowCount; j++)
        {
            std::cout << matrix[j * rowCount + col] << '\n';
        }
    }

    template <typename T> void Matrix<T>::SetValue(const int64_t row, const int64_t col, const T value)
    {
        matrix[row * colCount + col] = value;

        CalculateDeterminant();
    }
    template <typename T> void Matrix<T>::SetRand(const int64_t row, const int64_t col, const int64_t max_excluded)
    {
        matrix[row * colCount + col] = GetRand(0, max_excluded);

        CalculateDeterminant();
    }
    template <typename T> void Matrix<T>::FillValue(const T value)
    {
        for (size_t i = 0; i < rowCount * colCount; i++)
        {
            matrix[i] = value;
        }

        CalculateDeterminant();
    }
    template <typename T> void Matrix<T>::FillRand(const T max_excluded)
    {
        for (size_t i = 0; i < rowCount * colCount; i++)
        {
            matrix[i] = GetRand(0, max_excluded);
        }

        CalculateDeterminant();
    }

    template <typename T> void Matrix<T>::Transpose()
    {
        assert(rowCount > 0 && colCount > 0);

        Matrix<T> copy(*this);

        for (size_t i = 0; i < rowCount; i++)
        {
            for (size_t j = 0; j < colCount; j++)
            {
                matrix[i * colCount + j] = copy.matrix[j * rowCount + i];
            }
        }

        std::swap(rowCount, colCount);

        CalculateDeterminant();
    }
    template <typename T> void Matrix<T>::ConvertToUnit()
    {
        assert(rowCount > 0 && rowCount == colCount);

        for (size_t i = 0; i < rowCount; i++)
        {
            for (size_t j = 0; j < colCount; j++)
            {
                matrix[i * colCount + j] = (i == j ? 1 : 0);
            }
        }

        determinant = 1;
    }
    template <typename T> void Matrix<T>::Add(const Matrix<T>& second)
    {
        assert(rowCount == second.rowCount && colCount == second.colCount);

        for (size_t i = 0; i < rowCount; i++)
        {
            for (size_t j = 0; j < colCount; j++)
            {
                if (second.matrix[i * colCount + j] != 0)
                {
                    matrix[i * colCount + j] += second.matrix[i * colCount + j];
                }
            }
        }

        CalculateDeterminant();
    }
    template <typename T> void Matrix<T>::Subtract(const Matrix<T>& second)
    {
        assert(rowCount == second.rowCount && colCount == second.colCount);

        for (size_t i = 0; i < rowCount; i++)
        {
            for (size_t j = 0; j < colCount; j++)
            {
                if (second.matrix[i * colCount + j] != 0)
                {
                    matrix[i * colCount + j] -= second.matrix[i * colCount + j];
                }
            }
        }

        CalculateDeterminant();
    }
    template <typename T> void Matrix<T>::Multiply(const Matrix<T>& second)
    {
        assert(colCount == second.rowCount);

        Matrix<T> temp(rowCount, second.colCount);

        for (size_t i = 0; i < rowCount; i++)
        {
            for (size_t k = 0; k < second.colCount; k++)
            {
                T sum = 0;

                for (size_t j = 0; j < colCount; j++)
                {
                    if (matrix[i * colCount + j] != 0 && second.matrix[j * second.colCount + k] != 0)
                    {
                        sum += matrix[i * colCount + j] * second.matrix[j * second.colCount + k];
                    }
                }

                temp.matrix[i * temp.colCount + k] = sum;
            }
        }

        *this = std::move(temp);

        CalculateDeterminant();
    }
    template <typename T> void Matrix<T>::Multiply(const T k)
    {
        if (k == static_cast<T>(1))
        {
            return;
        }

        for (size_t i = 0; i < rowCount; i++)
        {
            for (size_t j = 0; j < colCount; j++)
            {
                matrix[i * colCount + j] *= k;
            }
        }

        CalculateDeterminant();
    }
    
    template <typename T> Matrix<T>* Matrix<T>::AddedMatrix(const Matrix<T>& src) const
    {
        assert(rowCount == src.rowCount && colCount == src.colCount);

        Matrix<T>* newm = new Matrix<T>(*this);
        newm->Add(src);

        return newm;
    }
    template <typename T> Matrix<T>* Matrix<T>::SubtractedMatrix(const Matrix<T>& src) const
    {
        assert(rowCount == src.rowCount && colCount == src.colCount);

        Matrix<T>* newm = new Matrix<T>(*this);
        newm->Subtract(src);

        return newm;
    }
    template <typename T> Matrix<T>* Matrix<T>::MultipliedMatrix(const Matrix<T>& src) const
    {
        assert(colCount == src.rowCount);

        Matrix<T>* newm = new Matrix<T>(*this);
        newm->Multiply(src);
        
        return newm;
    }
    template <typename T> Matrix<T>* Matrix<T>::TransposedMatrix() const
    {
        Matrix<T>* newm = new Matrix<T>(colCount, rowCount);

        for (size_t j = 0; j < colCount; j++)
        {
            for (size_t i = 0; i < rowCount; i++)
            {
                newm->matrix[j * rowCount + i] = matrix[i * colCount + j];
            }
        }

        newm->CalculateDeterminant();

        return newm;
    }
    template <typename T> Matrix<T>* Matrix<T>::MinorMatrix(const int64_t row, const int64_t col) const
    {
        Matrix<T>* newm = new Matrix<T>(rowCount - 1, colCount - 1);

        T x = 0;
        T y ;

        for (size_t i = 0; i < rowCount; i++)
        {
            if (i == row)
            {
                x = 1;
                continue;
            }

            y = 0;

            for (size_t j = 0; j < colCount; j++)
            {
                if (j == col)
                {
                    y = 1;
                }
                else
                {
                    newm->matrix[(x == 1 ? i - 1 : i) * newm->colCount + (y == 1 ? j - 1 : j)] = matrix[i * colCount + j];
                }
            }
        }

        newm->CalculateDeterminant();

        return newm;
    }
    template <typename T> Matrix<T>* Matrix<T>::AdjacentMatrix() const
    {
        Matrix<T>* newm = new Matrix<T>(rowCount, colCount);

        for (size_t i = 0; i < rowCount; i++)
        {
            for (size_t j = 0; j < colCount; j++)
            {
                Matrix<T>* minor = MinorMatrix(i, j);

                newm->SetValue(i, j, minor->GetDeterminant() * ((i + j) % 2 == 0 ? 1 : -1));

                delete minor;
            }
        }

        newm->Transpose();

        return newm;
    }
    template <typename T> Matrix<T>* Matrix<T>::InverseMatrix() const
    {
        if (CalculateDeterminant() != 0 && CalculateDeterminant() != INT64_MIN) // (detInitialized && determinant != 0)
        {
            Matrix<T>* adj = AdjacentMatrix();
            Matrix<T>* newm = new Matrix<T>(std::move(*adj));

            delete adj;

            newm->Multiply(1 / static_cast<double>(GetDeterminant()));

            return newm;
        }

        return nullptr;
    }
    
    template <typename T> void Matrix<T>::CalculateDeterminant()
    {
        if (rowCount != colCount || rowCount > 11)
        {
            return;
        }

        determinant = 0;

        switch (rowCount)
        {
        case 1:
        {
            determinant = matrix[0];
        }
        break;

        case 2:
        {
            determinant = (matrix[0] * matrix[colCount + 1] - matrix[1] * matrix[colCount]);
        }
        break;

        case 3:
        {
            for (size_t k = 0; k < 2; k++)
            {
                for (size_t i = 0; i < 3; i++)
                {
                    T prod = 1;

                    for (size_t j = 0; j < 3; j++)
                    {
                        prod *= matrix[((i + (k == 0 ? j : 2 - j)) % 3) * colCount + j];
                    }

                    determinant += prod * (k == 0 ? 1 : -1);
                }
            }
        }
        break;

        default:
        {
            for (size_t i = 0; i < rowCount; i++)
            {
                Matrix<T>* newm = MinorMatrix(i, 0);
                
                determinant += matrix[i * colCount] * newm->GetDeterminant() * (i % 2 == 0 ? 1 : -1);

                delete newm;
            }
        }
        break;
        }

        detInitialized = true;
    }

    template <typename T> static T Matrix<T>::GetRand(T first, T last)
    {
        std::uniform_real_distribution<double> distribution(first, last);
        std::random_device rd;
        std::default_random_engine rng(rd());

        return static_cast<T>(distribution(rng));
    }
    template <typename T> T Matrix<T>::GetValue(const int64_t row, const int64_t col) const
    {
        return matrix[row * colCount + col];
    }
    template <typename T> T Matrix<T>::GetDeterminant() const
    {
        return detInitialized ? determinant : INT64_MIN;
    }
    
    template <typename T> Matrix<T>  Matrix<T>::operator ~  ()
    {
        Matrix<T>* p = TransposedMatrix();
        Matrix<T> newm(std::move(*p));

        delete p;

        return newm;
    }
    template <typename T> Matrix<T>  Matrix<T>::operator !  ()
    {
        Matrix<T>* p = InverseMatrix();
        Matrix<T> newm(std::move(*p));

        delete p;

        return newm;
    }

    template <typename T> Matrix<T>  Matrix<T>::operator +  (const Matrix<T>& src)
    {
        Matrix<T>* p = AddedMatrix(src);
        Matrix<T> newm(std::move(*p));

        delete p;

        return newm;
    }
    template <typename T> Matrix<T>  Matrix<T>::operator -  (const Matrix<T>& src)
    {
        Matrix<T>* p = SubtractedMatrix(src);
        Matrix<T> newm(std::move(*p));

        delete p;

        return newm;
    }
    template <typename T> Matrix<T>  Matrix<T>::operator *  (const Matrix<T>& src)
    {
        Matrix<T>* p = MultipliedMatrix(src);
        Matrix<T> newm(std::move(*p));

        delete p;

        return newm;
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