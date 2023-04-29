#pragma once

#include <iostream>
#include <vector>
#include <array>

using namespace std;

class matrix
{
private:
    vector<vector<double>> _matrix;
    int _row = 0;
    int _col = 0;

    double calculateSarrus();
    double calculateDeterminant();

    double get_rand(double first, double last);


public:
    matrix();
    ~matrix();
    matrix(int row, int col);
    matrix(matrix& source);
    matrix(double* arr, double length, int row, int col);
    matrix(vector<double> vec, int row, int col);

    void printAll();
    void printRow(int row);
    void printCol(int col);

    void toUnit();
    void setValue(int row, int col, int value);
    void setValue(int row, int col, double value);
    void setRand(int row, int col, int max);
    void setRand(int row, int col, double max);
    void fillValue(int value);
    void fillValue(double value);
    void fillRand(int max);
    void fillRand(double max);
    
    void transPose();
    void addMatrix(matrix& second);
    void subtractMatrix(matrix& second);
    void multiplyMatrix(matrix& second);
    void multiplyScalar(int k);
    void multiplyScalar(double k);
    
    matrix TransPosedMatrix();
    matrix AddedMatrix(matrix& second);
    matrix SubtractedMatrix(matrix& second);
    matrix MultipledMatrix(matrix& second);
    matrix MinorMatrix(int row, int col);
    matrix AdjacentMatrix();
    matrix InverseMatrix();
    
    double getSarrus();
    double getDeterminant();
    
    matrix operator + (matrix& source);
    matrix operator - (matrix& source);
    matrix operator * (matrix& source);
};
