#ifndef HEAT_EQUATION_MATRIX_H
#define HEAT_EQUATION_MATRIX_H

#include <map>
#include <array>
#include <sstream>
#include <cmath>
#include <unordered_map>

#include "vector.hpp"

typedef unsigned short idx;
typedef std::array<idx, 2> key;

struct pair_hash {
public:
    std::size_t operator()(const key& key) const {
        return (key[0] << 16u) | key[1];
    }
};

template <typename T>
class Matrix {
public:
    typedef std::unordered_map<key, T, pair_hash> map;

    const int rows;
    const int columns;
    map elements;

    /** Constructors **/
    Matrix(int m, int n) : rows(m), columns(n) {}

    /** Operators **/
    T& operator[](const key& key) {
        idx keyI = key[0];
        idx keyJ = key[1];
        if (keyI >= rows || keyJ >= columns) {
            std::cerr << "Error: key is out of matrix boundaries." << std::endl;
            throw std::exception();
        }

        return elements[key];
    }

    /** Utility matrix printing method (not for use with big matrices) **/
    void dump() const {
        std::stringstream ss; // string builder for displaying elements in the matrix

        auto copyEls(elements); // work on matrix copy so as not to create unnecessary zeros in the original map

        for (idx i = 0; i < rows; ++i) {
            for (idx j = 0; j < columns; ++j) {
                ss << std::round(copyEls[{i, j}] * 1000) / 1000.;
                for (int k = ss.str().size(); k < 6; ++k) { // always display 6 characters
                    ss << " "; // add trailing spaces
                }
                std::cout << ss.str() << "\t";
                ss = std::stringstream(); // reinitialize stream
            }
            std::cout << std::endl; // change row
        }
    }

    /** Destructor **/
    virtual ~Matrix() = default;
};

/** Matrix-vector multiplication **/
template<typename T>
Vector<T> operator*(const Matrix<T>& lhs, const Vector<T>& rhs) {
    if (lhs.rows != rhs.length) {
        std::cerr << "Error: matrix-vector dimensions must agree." << std::endl;
        throw std::exception();
    }

    Vector<T> out = Vector<T>(rhs.length);
    for (auto & element : lhs.elements) { // skip null (i, j) pairs by iterating on the present elements
        // element.first[0] = i, element.first[1] = j, element.second = value
        out.data[element.first[0]] += element.second * rhs.data[element.first[1]];
    }
    return out;
}

#endif //HEAT_EQUATION_MATRIX_H
