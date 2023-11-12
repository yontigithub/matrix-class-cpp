//
// Created by Yonatan Rappoport on 12/11/2023.
//

#ifndef MATRIX_CLASS_CPP_UTILS_H
#define MATRIX_CLASS_CPP_UTILS_H

#include <iostream>

int len(int n) {
    int ans = 0;

    if(n == 0) return 1;

    if (n < 0) {
        ans++;
        n *= -1;
    }

    while(n) {
        n /= 10;
        ++ans;
    }

    return ans;
}
int len(const std::string &s)
{return (int)s.size();}

void print(std::ostream& os, const int &n, const int &padding) {
    for(int k = 0; k < (padding - len(n))/2; ++k) os << ' ';
    os << n;
    for(int k = 0; k < (padding - len(n) + 1)/2; ++k) os << ' ';
}
void print(std::ostream& os, const std::string &s, const int &padding) {
    for(int k = 0; k < (padding - s.size())/2; ++k) os << ' ';
    os << s;
    for(int k = 0; k < (padding - s.size() + 1)/2; ++k) os << ' ';
}


template <class T>
std::pair<T, T> reverse(std::pair<T, T> a) {
    return std::pair<T,T>(a.second, a.first);
}

#endif //MATRIX_CLASS_CPP_UTILS_H
