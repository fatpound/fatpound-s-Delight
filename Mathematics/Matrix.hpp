#pragma once

#include "fatpound.hpp"

namespace fatpound
{
    namespace math
    {
        template <typename T>
        class Matrix
        {
        private:
            T calculateSarrus();
            T calculateDeterminant();
            T get_rand(T first, T last);


        protected:


        public:
            std::vector<std::vector<T>> matris;

            int row_count = 0;
            int col_count = 0;

            Matrix();
            ~Matrix();
            Matrix(int row, int col);
            Matrix(Matrix<T>& source);
            Matrix(T* arr, T length, int row, int col);
            Matrix(std::vector<T> vec, int row, int col);
            Matrix(std::vector<std::vector<T>> vec);

            void printAll();
            void printRow(int row);
            void printCol(int col);

            void toUnit();
            void setValue(int row, int col, T value);
            void setRand(int row, int col, int max);
            void fillValue(T value);
            void fillRand(T max);

            void transPose();
            void addMatrix(Matrix<T>& second);
            void subtractMatrix(Matrix<T>& second);
            void multiplyMatrix(Matrix<T>& second);
            void multiplyScalar(T k);

            Matrix<T> TransPosedMatrix();
            Matrix<T> AddedMatrix(Matrix<T>& second);
            Matrix<T> SubtractedMatrix(Matrix<T>& second);
            Matrix<T> MultipledMatrix(Matrix<T>& second);
            Matrix<T> MinorMatrix(int row, int col);
            Matrix<T> AdjacentMatrix();
            Matrix<T> InverseMatrix();

            T getSarrus();
            T getDeterminant();

            Matrix<T>& operator + (Matrix<T>& source);
            Matrix<T>& operator - (Matrix<T>& source);
            Matrix<T>& operator * (Matrix<T>& source);
        };

        template <typename T> T Matrix<T>::get_rand(T first, T last)
        {
            std::uniform_real_distribution<double> distribution(first, last);
            std::random_device rd;
            std::default_random_engine generator(rd());

            return distribution(generator);
        }

        template <typename T> Matrix<T>::Matrix()
        {

        }
        template <typename T> Matrix<T>::~Matrix()
        {

        }
        template <typename T> Matrix<T>::Matrix(int row, int col)
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
        template <typename T> Matrix<T>::Matrix(Matrix<T>& source)
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
        template <typename T> Matrix<T>::Matrix(T* arr, T length, int row, int col)
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
        template <typename T> Matrix<T>::Matrix(std::vector<T> vec, int row, int col)
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
        template <typename T> Matrix<T>::Matrix(std::vector<std::vector<T>> vec)
        {
            this->matris = std::vector<std::vector<T>>(vec);
        }

        template <typename T> void Matrix<T>::printAll()
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
        template <typename T> void Matrix<T>::printRow(int row)
        {
            for (int i = 0; i < this->col_count; i++)
            {
                std::cout << this->matris.at(row).at(i) << " ";
            }

            std::cout << '\n';
        }
        template <typename T> void Matrix<T>::printCol(int col)
        {
            for (int i = 0; i < this->row_count; i++)
            {
                std::cout << this->matris.at(i).at(col) << '\n';
            }
        }

        template <typename T> void Matrix<T>::toUnit()
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
        template <typename T> void Matrix<T>::setValue(int row, int col, T value)
        {
            this->matris.at(row).at(col) = value;
        }
        template <typename T> void Matrix<T>::setRand(int row, int col, int max)
        {
            max++;
            this->matris.at(row).at(col) = (T)(int)get_rand(0, max);
        }
        template <typename T> void Matrix<T>::fillValue(T value)
        {
            for (int i = 0; i < this->row_count; i++)
            {
                for (int j = 0; j < this->col_count; j++)
                {
                    this->matris.at(i).at(j) = value;
                }
            }
        }
        template <typename T> void Matrix<T>::fillRand(T max)
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

        template <typename T> void Matrix<T>::transPose()
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
        template <typename T> void Matrix<T>::addMatrix(Matrix<T>& second)
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
        template <typename T> void Matrix<T>::subtractMatrix(Matrix<T>& second)
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
        template <typename T> void Matrix<T>::multiplyMatrix(Matrix<T>& second)
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
        template <typename T> void Matrix<T>::multiplyScalar(T k)
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

        template <typename T> Matrix<T> Matrix<T>::TransPosedMatrix()
        {
            Matrix newm = Matrix(this->col_count, this->row_count);

            for (int j = 0; j < this->col_count; j++)
            {
                for (int i = 0; i < this->row_count; i++)
                {
                    newm.matris.at(j).at(i) = this->matris.at(i).at(j);
                }
            }

            return newm;
        }
        template <typename T> Matrix<T> Matrix<T>::AddedMatrix(Matrix<T>& second)
        {
            if (this->row_count == second.row_count && this->col_count == second.col_count)
            {
                Matrix newm = Matrix(*this);

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
        template <typename T> Matrix<T> Matrix<T>::SubtractedMatrix(Matrix<T>& second)
        {
            if (this->row_count == second.row_count && this->col_count == second.col_count)
            {
                Matrix newm = Matrix(*this);

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
        template <typename T> Matrix<T> Matrix<T>::MultipledMatrix(Matrix<T>& second)
        {
            if (this->col_count == second.row_count)
            {
                Matrix newmatris = Matrix(this->row_count, second.col_count);

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
        template <typename T> Matrix<T> Matrix<T>::MinorMatrix(int row, int col)
        {
            Matrix src = Matrix(this->row_count - 1, this->col_count - 1);

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
        template <typename T> Matrix<T> Matrix<T>::AdjacentMatrix()
        {
            Matrix newm = Matrix(this->row_count, this->col_count);

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
        template <typename T> Matrix<T> Matrix<T>::InverseMatrix()
        {
            calculateDeterminant();

            if (this->getDeterminant() != 0)
            {
                Matrix newm = AdjacentMatrix();

                newm.multiplyScalar(1 / this->getDeterminant());

                return newm;
            }
        }

        template <typename T> T Matrix<T>::calculateSarrus()
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
        template <typename T> T Matrix<T>::calculateDeterminant()
        {
            T det = 0;

            for (int i = 0; i < this->row_count; i++)
            {
                Matrix newm = MinorMatrix(i, 0);

                det += this->matris.at(i).at(0) * newm.calculateDeterminant() * (i % 2 == 0 ? 1 : -1);
            }

            return det;
        }

        template <typename T> T Matrix<T>::getSarrus()
        {
            if (this->row_count != this->col_count || this->row_count > 3)
                return INT32_MIN;

            if (this->row_count < 3)
            {
                return (this->row_count == 1 ? this->matris.at(0).at(0) : (this->matris.at(0).at(0) * this->matris.at(1).at(1) - this->matris.at(0).at(1) * this->matris.at(1).at(0)));
            }

            return calculateSarrus();
        }
        template <typename T> T Matrix<T>::getDeterminant()
        {
            if (this->row_count != this->col_count)
                return INT32_MIN;

            if (this->row_count < 4 && this->col_count < 4)
                return getSarrus();

            return calculateDeterminant();
        }

        template <typename T> Matrix<T>& Matrix<T>::operator + (Matrix<T>& source)
        {
            return AddedMatrix(source);
        }
        template <typename T> Matrix<T>& Matrix<T>::operator - (Matrix<T>& source)
        {
            return SubtractedMatrix(source);
        }
        template <typename T> Matrix<T>& Matrix<T>::operator * (Matrix<T>& source)
        {
            return MultipledMatrix(source);
        }
    }
}
