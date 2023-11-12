//
// Created by Yonatan Rappoport on 12/11/2023.
//

#include <iostream>
#include "Exceptions.h"

const char* InvalidDimensions::what() const noexcept {
    return "Error. Invalid Dimensions.";
}

const char* InvalidType::what() const noexcept {
    return "Error. Invalid Type.";
}

const char* InvalidOperation::what() const noexcept {
    return "Error. Invalid Operation.";
}

