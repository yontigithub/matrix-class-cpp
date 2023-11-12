//
// Created by Yonatan Rappoport on 12/11/2023.
//

#include <iostream>
#include "Matrix.h"
using namespace std;


int main() {
    Matrix<int> m({5,5}, 'I');

    Matrix<int> x = 500 * m;

    cout << (x.transpose());
}