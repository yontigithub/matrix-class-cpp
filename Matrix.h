//
// Created by Yonatan Rappoport on 12/11/2023.
//

#ifndef MATRIX_CLASS_CPP_MATRIX_H
#define MATRIX_CLASS_CPP_MATRIX_H

#include <iostream>
#include <vector>
#include "Exceptions.h"
using namespace std;

template <class T>
class Matrix {
public:
    explicit Matrix(const pair<int, int> &dimensions);
    Matrix(const pair<int, int> &dimensions, bool input);
    Matrix(const pair<int, int> &dimensions, const char &type);
    explicit Matrix(vector<vector<T>> matrix);
    Matrix(const Matrix<T> &m);
    ~Matrix() = default;

    pair<int, int> getDimensions() const;
    void write(const int &row, const int &column, const T &val);
    T read(const int &row, const int &column) const;
    Matrix<T>& transpose() const;

private:
    vector<vector<T>> m_matrix;
};


// ------------------------ Implementation ------------------------

template <class T>
static pair<T, T> reverse(pair<T, T> a) {
    return pair<T,T>(a.second, a.first);
}

template <class T>
Matrix<T>::Matrix(const pair<int, int> &dimensions) :
        m_matrix(vector<vector<T>>(dimensions.first, vector<T>(dimensions.second, 0)))
{
    if(dimensions.first <= 0 || dimensions.second <= 0) {
        throw InvalidDimensions();
    }
}

template <class T>
Matrix<T>::Matrix(const pair<int, int> &dimensions, bool input) :
        m_matrix(vector<vector<T>>(dimensions.first, vector<T>(dimensions.second, 0)))
{
    if(dimensions.first <= 0 || dimensions.second <= 0) {
        throw InvalidDimensions();
    }

    if(input) {
        for (int i = 0; i < dimensions.first; ++i) {
            for (int j = 0; j < dimensions.second; ++j) {
                T temp; cin >> temp;
                m_matrix[i][j] = temp;
            }
        }
    }
}

template <class T>
Matrix<T>::Matrix(const pair<int, int> &dimensions, const char &type) :
        m_matrix(vector<vector<T>>(dimensions.first, vector<T>(dimensions.second, 0)))
{
    if (type == 'I' || type == 'i' || type == '1') {
        if (dimensions.first != dimensions.second) {
            throw InvalidDimensions();
        }

        for (int i = 0; i < dimensions.first; ++i) {
            m_matrix[i][i] = 1;
        }
    } else if (type != '0' && type != 'O' && type != 'o') {
        throw InvalidType();
    }
}

template <class T>
Matrix<T>::Matrix(vector<vector<T>> matrix) : m_matrix(matrix) {

}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &m) : Matrix<T>(m.getDimensions()) {
    for (int i = 0; i < m.getDimensions().first; ++i) {
        for (int j = 0; j < m.getDimensions().second; ++j) {
            m_matrix[i][j] = m.read(i,j);
        }
    }
} // Constructors

template <class T>
void Matrix<T>::write(const int &row, const int &column, const T &val) {
    pair<int, int> d = getDimensions();

    if(row < 0 || row >= d.first || column < 0 || column >= d.second) {
        throw InvalidDimensions();
    }

    m_matrix[row][column] = val;
}

template <class T>
T Matrix<T>::read(const int &row, const int &column) const {
    return m_matrix[row][column];
}

template <class T>
pair<int, int> Matrix<T>::getDimensions() const {
    return pair<int, int>(m_matrix.size(), m_matrix[0].size());
}

template <class T>
Matrix<T>& Matrix<T>::transpose() const {
    auto res = new Matrix<T>(reverse(getDimensions()));

    for(int i = 0; i < getDimensions().first; ++i) {
        for(int j = 0; j < getDimensions().second; ++j) {
            res->write(j, i, m_matrix[i][j]);
        }
    }

    return *res;
} // Methods

template <class T>
Matrix<T>& operator*(const Matrix<T> &a, const T &b) {

    auto res = new Matrix<T>(a.getDimensions());

    for(int i = 0; i < a.getDimensions().first; ++i) {
        for(int j = 0; j < a.getDimensions().second; ++j) {
            res->write(i, j, a.read(i, j) * b);
        }
    }

    return *res;
}

template <class T>
Matrix<T>& operator*(const T &b, const Matrix<T> &a) {
    return a*b;
}

template <class T>
Matrix<T>& operator+(const Matrix<T> &a, const Matrix<T> &b) {
    if (a.getDimensions() != b.getDimensions()) {
        throw InvalidDimensions();
    }

    auto res = new Matrix<T>(a.getDimensions());

    for(int i = 0; i < a.getDimensions().first; ++i) {
        for(int j = 0; j < a.getDimensions().second; ++j) {
            res->write(i, j, a.read(i, j) + b.read(i, j));
        }
    }

    return *res;
}

template <class T>
Matrix<T>& operator-(const Matrix<T> &a) {
    auto res = new Matrix<T>(a.getDimensions());

    for(int i = 0; i < a.getDimensions().first; ++i) {
        for(int j = 0; j < a.getDimensions().second; ++j) {
            res->write(i, j, -a.read(i, j));
        }
    }

    return *res;
}

template <class T>
Matrix<T>& operator-(const Matrix<T> &a, const Matrix<T> &b) {
    return a + -b;
}

template <class T>
Matrix<T>& operator*(const Matrix<T> &a, const Matrix<T> &b) {
    if (a.getDimensions().second != b.getDimensions().first) {
        throw InvalidDimensions();
    }

    auto res = new Matrix<T>({a.getDimensions().first, b.getDimensions().second});

    for(int i = 0; i < a.getDimensions().first; ++i) {
        for(int j = 0; j < b.getDimensions().second; ++j) {
            for(int k = 0; k < a.getDimensions().second; ++k) {
                res->write(i, j, res->read(i,j) + a.read(i, k) * b.read(k, j));
            }
        }
    }

    return *res;
}

template <class T>
Matrix<T>& operator^(const Matrix<T> &m, const int& n) {
    if (n <= 0) {
        throw InvalidOperation();
    }

    if (m.getDimensions().first != m.getDimensions().second) {
        throw InvalidDimensions();
    }

    auto res = new Matrix<T>(m.getDimensions(), 'I');

    for(int i = 0; i < n; ++i) {
        *res = *res * m;
    }

    return *res;
}  // Operators


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
int len(const string &s)
{return (int)s.size();}

void print(std::ostream& os, const int &n, const int &padding) {
    for(int k = 0; k < (padding - len(n))/2; ++k) os << ' ';
    os << n;
    for(int k = 0; k < (padding - len(n) + 1)/2; ++k) os << ' ';
}
void print(std::ostream& os, const string &s, const int &padding) {
    for(int k = 0; k < (padding - s.size())/2; ++k) os << ' ';
    os << s;
    for(int k = 0; k < (padding - s.size() + 1)/2; ++k) os << ' ';
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T> &m) {
    int maxLen = 0;
    for(int i = 0; i < m.getDimensions().first; ++i) {
        for (int j = 0; j < m.getDimensions().second; ++j) {
            if (len(m.read(i,j)) > maxLen) {
                maxLen = len(m.read(i,j));
            }
        }
    }

    int padding = maxLen + 2;

    if (m.getDimensions().first == 1) {
        os << "( ";
        for(int i = 0; i < m.getDimensions().second; ++i)
            os << m.read(0, i) << ' ';
        os << ')';
    } else {
        os << "/";
        for (int i = 0; i < m.getDimensions().second; ++i)
            print(os, m.read(0, i), padding);
        os << "\\\n";

        for (int i = 1; i < m.getDimensions().first - 1; ++i) {
            os << "|";
            for(int j = 0; j < m.getDimensions().second; ++j)
                print(os, m.read(i,j), padding);
            os << "|\n";
        }

        os << "\\";
        for (int i = 0; i < m.getDimensions().second; ++i)
            print(os, m.read(m.getDimensions().first - 1, i), padding);
        os << '/';
    }

    return os;
} // Printing

#endif //MATRIX_CLASS_CPP_MATRIX_H
