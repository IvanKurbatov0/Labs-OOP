#include "matrix.h"
#include <iostream>
#include <QString>
using namespace std;

matrix::matrix(int n)
{
    this->n = n;
    Matrix = new number * [n];
    for (int i = 0; i < n; i++)
    {
        Matrix[i] = new number[n]{ 1 };
    }
}

matrix::matrix(const matrix& m)
{
    if (this != &m)
    {
        n = m.n;
        Matrix = new number *[n];
        for (int i = 0; i < n; i ++)
        {
            Matrix[i] = new number[n];
            for (int j = 0; j < n; j++)
            {
                Matrix[i][j] = m.Matrix[i][j];
            }
        }
    }
}


matrix::~matrix()
{
    for (int i = 0; i < n; i++)
    {
        delete[] Matrix[i];
    }
    delete[] Matrix;
}

void matrix::InterIn(int i, int j,  number a)
{
    Matrix[i][j]=a;
}
void matrix::in()
{
    std::cout<<"\n" << "Enter n*n elements:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout<< "\n" << ">";
            std::cin >> Matrix[i][j];
        }
    }
}


void matrix::output()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << Matrix[i][j]<<" ";
        }
        std::cout << "\n";
    }
}

void matrix::trans()
{

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            std::swap(Matrix[i][j], Matrix[j][i]);
        }
    }
}


void matrix::operationP(int str1, int str2)
{
    for (int i = 0; i < n; i++)
    {
        number t = Matrix[str1][i];
        Matrix[str1][i] = Matrix[str2][i];
        Matrix[str2][i] = t;
    }
}


void matrix::operationM(int str1, int str2, number a)
{
    for (int i = 0; i < n; i++)
    {
        Matrix[str1][i] = Matrix[str2][i] * a + Matrix[str1][i];
    }
}


matrix matrix::diag()
{
    matrix m = *this;
    int j = 0;
    for (int i = 0; i < n && j < n; i++)
    {
        if (m.Matrix[i][j] == 0) {
            for (int k = i + 1; k < n; k++) {
                if (m.Matrix[k][j] != 0)
                {
                    m.operationP(i, k);
                }
            }
        }
        if (m.Matrix[i][j] != 0) {
            for (int k = i + 1; k < n; k++)
            {
                m.operationM(k, i, -m.Matrix[k][j] / m.Matrix[i][j]);
            }
        }
        else
            i--;
        j++;
    }
    return m;
}


number matrix::det()
{
    number det=1;
    matrix m = this->diag();
    for (int i = 0; i < n; i++)
    {
        det = m.Matrix[i][i] * det;
    }
    return det;
}



int matrix::rank()
{
    int rank = 0;
    matrix m = this->diag();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (m.Matrix[i][j] != 0)
            {
                rank++;
                break;
            }
        }
    }
    return rank;
}


matrix& matrix::operator=(const matrix& m)
{
    if (this != &m)
    {
        this->~matrix();
        n = m.n;
        Matrix = new number *[n];
        for (int i = 0; i < n; i++)
        {
            Matrix[i] = new number[n];
            for (int j = 0; j < n; j++)
            {
                Matrix[i][j] = m.Matrix[i][j];
            }
        }
        return *this;
    }
}

number matrix::get(int i, int j)
{
    return Matrix[i][j];
}
