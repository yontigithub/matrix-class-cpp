//
// Created by Yonatan Rappoport on 12/11/2023.
//

#ifndef MATRIX_CLASS_CPP_EXCEPTIONS_H
#define MATRIX_CLASS_CPP_EXCEPTIONS_H

class InvalidDimensions : std::exception {
public:
    explicit InvalidDimensions() = default;
    const char* what() const noexcept override;
};


class InvalidType : std::exception {
public:
    explicit InvalidType() = default;
    const char* what() const noexcept override;
};


class InvalidOperation : std::exception {
public:
    explicit InvalidOperation() = default;
    const char* what() const noexcept override;
};

#endif //MATRIX_CLASS_CPP_EXCEPTIONS_H
