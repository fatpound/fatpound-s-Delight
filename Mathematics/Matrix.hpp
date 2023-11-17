#pragma once

#include <iostream>
#include <memory>
#include <random>
#include <algorithm>
#include <cassert>

namespace fatpound::math
{
    template <typename T>
    class Matrix
    {
    public:
        Matrix() = delete;
        ~Matrix() = default;
        Matrix(const Matrix<T>& src)
            :
            rowCount_{ src.rowCount_ },
            colCount_{ src.colCount_ },
            matrix_{ std::make_unique<T[]>(rowCount_ * colCount_) }
        {
            std::copy(src.matrix_.get(), src.matrix_.get() + rowCount_ * colCount_, matrix_.get());
        }
        Matrix(Matrix<T>&& src) noexcept
            :
            rowCount_{ std::exchange(src.rowCount_, 0ull) },
            colCount_{ std::exchange(src.colCount_, 0ull) },
            matrix_{ std::move(src.matrix_) }
        {

        }
        Matrix<T>& operator = (const Matrix<T>& src)
        {
            rowCount_ = src.rowCount_;
            colCount_ = src.colCount_;
            matrix_ = std::make_unique<T[]>(rowCount_ * colCount_);

            std::copy(src.matrix_.get(), src.matrix_.get() + rowCount_ * colCount_, matrix_.get());

            return *this;
        }
        Matrix<T>& operator = (Matrix<T>&& src) noexcept
        {
            if (this != std::addressof(src))
            {
                rowCount_ = std::exchange(src.rowCount_, 0ull);
                colCount_ = std::exchange(src.colCount_, 0ull);
                matrix_ = std::move(src.matrix_);
            }

            return *this;
        }

        Matrix(int64_t row, int64_t col)
            :
            rowCount_{ (assert(row > 0), static_cast<size_t>(row)) },
            colCount_{ (assert(col > 0), static_cast<size_t>(col)) },
            matrix_{ std::make_unique<T[]>(rowCount_ * colCount_) }
        {
            
        }


    public:
        void Print() const
        {
            for (size_t i = 0; i < rowCount_; ++i)
            {
                PrintRow(i);
            }

            std::cout << '\n';
        }
        void PrintRow(size_t row) const
        {
            for (size_t i = 0; i < colCount_; ++i)
            {
                std::cout << matrix_[row * colCount_ + i] << ' ';
            }

            std::cout << '\n';
        }
        void PrintColumn(size_t col) const
        {
            for (size_t j = 0; j < rowCount_; ++j)
            {
                std::cout << matrix_[j * rowCount_ + col] << '\n';
            }
        }

        void SetRand(size_t row, size_t col, size_t max_included)
        {
            std::default_random_engine drng(std::random_device{}());
            std::uniform_real_distribution<double> ddist(0.0, max_included);

            matrix_[row * colCount_ + col] = static_cast<T>(ddist(drng));
        }
        void FillValue(const T& value)
        {
            std::fill(matrix_.get(), matrix_.get() + rowCount_ * colCount_, value);
        }
        void FillRand(const T& max_included)
        {
            std::default_random_engine drng(std::random_device{}());
            std::uniform_real_distribution<double> ddist(0.0, max_included);

            std::generate(matrix_.get(), matrix_.get() + rowCount_ * colCount_, [&]() { return static_cast<T>(ddist(drng)); });
        }

        void Transpose()
        {
            static_assert(rowCount_ > 0 && colCount_ > 0);

            Matrix<T> copy(*this);

            for (size_t i = 0; i < rowCount_; ++i)
            {
                for (size_t j = 0; j < colCount_; ++j)
                {
                    matrix_[i * colCount_ + j] = copy.matrix_[j * rowCount_ + i];
                }
            }

            std::swap(rowCount_, colCount_);
        }
        void ConvertToUnit()
        {
            static_assert(rowCount_ > 0 && rowCount_ == colCount_);

            for (size_t i = 0; i < rowCount_ * colCount_; i += rowCount_)
            {
                matrix_[i] = 1;
                ++i;
            }
        }
        void Add(const Matrix<T>& second)
        {
            static_assert(rowCount_ == second.rowCount_ && colCount_ == second.colCount_);

            for (size_t i = 0; i < rowCount_ * colCount_; ++i)
            {
                matrix_[i] += second.matrix_[i];
            }
        }
        void Subtract(const Matrix<T>& second)
        {
            static_assert(rowCount_ == second.rowCount_ && colCount_ == second.colCount_);

            for (size_t i = 0; i < rowCount_ * colCount_; ++i)
            {
                matrix_[i] -= second.matrix_[i];
            }
        }
        void Multiply(const Matrix<T>& second)
        {
            static_assert(colCount_ == second.rowCount_);

            Matrix<T> temp(rowCount_, second.colCount_);

            for (size_t i = 0; i < rowCount_; ++i)
            {
                for (size_t k = 0; k < second.colCount_; ++k)
                {
                    T sum = 0;

                    for (size_t j = 0; j < colCount_; ++j)
                    {
                        if (matrix_[i * colCount_ + j] != 0 && second.matrix_[j * second.colCount_ + k] != 0)
                        {
                            sum += matrix_[i * colCount_ + j] * second.matrix_[j * second.colCount_ + k];
                        }
                    }

                    temp.matrix_[i * temp.colCount_ + k] = sum;
                }
            }

            *this = std::move(temp);
        }
        void Multiply(const T& k)
        {
            if (k == static_cast<T>(1ull))
            {
                return;
            }
            
            for (size_t i = 0; i < rowCount_ * colCount_; ++i)
            {
                matrix_[i] *= k;
            }
        }

        T  GetDeterminant() const
        {
            if (rowCount_ != colCount_ || rowCount_ > 11)
            {
                return std::numeric_limits<int64_t>::max();
            }

            T determinant = 0;

            switch (rowCount_)
            {
            case 1:
            {
                determinant = matrix_[0];
            }
            break;

            case 2:
            {
                determinant = (matrix_[0] * matrix_[colCount_ + 1] - matrix_[1] * matrix_[colCount_]);
            }
            break;

            case 3:
            {
                for (size_t k = 0; k < 2; ++k)
                {
                    for (size_t i = 0; i < 3; ++i)
                    {
                        T prod = 1;

                        for (size_t j = 0; j < 3; ++j)
                        {
                            prod *= matrix_[((i + (k == 0 ? j : 2 - j)) % 3) * colCount_ + j];
                        }

                        determinant += prod * (k == 0 ? 1 : -1);
                    }
                }
            }
            break;

            default:
            {
                for (size_t i = 0; i < rowCount_; ++i)
                {
                    Matrix<T> newm = MinorMatrix(i, 0);

                    determinant += matrix_[i * colCount_] * newm.GetDeterminant() * (i % 2 == 0 ? 1 : -1);
                }
            }
            break;
            }

            return determinant;
        }
        T  GetValue(size_t row, size_t col) const
        {
            return matrix_[row * colCount_ + col];
        }
        T& GetValue(size_t row, size_t col)
        {
            return matrix_[row * colCount_ + col];
        }
        
        Matrix<T>  operator +  (const Matrix<T>& src)
        {
            return AddedMatrix(src);
        }
        Matrix<T>  operator -  (const Matrix<T>& src)
        {
            return SubtractedMatrix(src);
        }
        Matrix<T>  operator *  (const Matrix<T>& src)
        {
            return MultipliedMatrix(src);
        }
        
        Matrix<T>& operator += (const Matrix<T>& src)
        {
            Add(src);

            return *this;
        }
        Matrix<T>& operator -= (const Matrix<T>& src)
        {
            Subtract(src);

            return *this;
        }
        Matrix<T>& operator *= (const Matrix<T>& src)
        {
            Multiply(src);

            return *this;
        }


    protected:


    private:
        Matrix<T> AddedMatrix(const Matrix<T>& src) const
        {
            Matrix<T> newm(*this);
            newm.Add(src);

            return newm;
        }
        Matrix<T> SubtractedMatrix(const Matrix<T>& src) const
        {
            Matrix<T> newm(*this);
            newm.Subtract(src);

            return newm;
        }
        Matrix<T> MultipliedMatrix(const Matrix<T>& src) const
        {
            Matrix<T> newm(*this);
            newm.Multiply(src);

            return newm;
        }
        Matrix<T> TransposedMatrix() const
        {
            Matrix<T> newm(colCount_, rowCount_);

            for (size_t j = 0; j < colCount_; ++j)
            {
                for (size_t i = 0; i < rowCount_; ++i)
                {
                    newm.matrix_[j * rowCount_ + i] = matrix_[i * colCount_ + j];
                }
            }

            return newm;
        }
        Matrix<T> MinorMatrix(size_t row, size_t col) const
        {
            Matrix<T> newm(rowCount_ - 1, colCount_ - 1);

            T x = 0;
            T y;

            for (size_t i = 0; i < rowCount_; ++i)
            {
                if (i == row)
                {
                    x = 1;
                    continue;
                }

                y = 0;

                for (size_t j = 0; j < colCount_; ++j)
                {
                    if (j == col)
                    {
                        y = 1;
                    }
                    else
                    {
                        newm.matrix_[(x == 1 ? i - 1 : i) * newm.colCount_ + (y == 1 ? j - 1 : j)] = matrix_[i * colCount_ + j];
                    }
                }
            }

            return newm;
        }
        Matrix<T> AdjacentMatrix() const
        {
            Matrix<T> newm(rowCount_, colCount_);

            for (size_t i = 0; i < rowCount_; ++i)
            {
                for (size_t j = 0; j < colCount_; ++j)
                {
                    Matrix<T> minor = MinorMatrix(i, j);

                    newm.SetValue(i, j, minor.GetDeterminant() * ((i + j) % 2 == 0 ? 1 : -1));
                }
            }

            newm.Transpose();

            return newm;
        }
        Matrix<T> InverseMatrix() const
        {
            T det = GetDeterminant();

            if (det != 0 && det != std::numeric_limits<int64_t>::min())
            {
                Matrix<T> newm = AdjacentMatrix();

                newm.Multiply(1.0 / static_cast<double>( GetDeterminant() ));

                return newm;
            }

            return Matrix<T>();
        }


    private:
        size_t rowCount_ = 0ull;
        size_t colCount_ = 0ull;

        std::unique_ptr<T[]> matrix_ = nullptr;
    };
}