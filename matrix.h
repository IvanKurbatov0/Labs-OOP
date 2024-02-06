#ifndef MATRIX_H
#define MATRIX_H

#include "number.h"

class matrix
{
    number **Matrix=nullptr;
    int n;
public:
    matrix(const matrix&);
    matrix(int);
    matrix diag();
    ~matrix();
    void output();
    void in();
    void trans();
    number det();
    int rank();
    void InterIn(int, int,  number);
    matrix& operator=(const matrix&);
    number get(int, int);
private:
    void operationP(int, int);
    void operationM(int, int, number);
};




#endif
