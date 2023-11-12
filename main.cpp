//
// Created by Yonatan Rappoport on 12/11/2023.
//

#include <iostream>
#include "Matrix.h"


int main() {
    Matrix<int> m({5,5}, 'I');

    Matrix<int> x = m * m;

    std::cout << x.transpose();
}