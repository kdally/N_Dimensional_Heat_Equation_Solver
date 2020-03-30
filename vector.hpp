#ifndef HEAT_EQUATION_VECTOR_H
#define HEAT_EQUATION_VECTOR_H

#include <iostream>
#include <iterator>
#include <memory>

template<typename T>
class Vector {
public:
    int length;
    T* data;

    /** Constructors **/
    // `Null' vector
    Vector() : length(0), data(new T[0]()) {}

    // Empty vector
    // marked as explicit so as to avoid unclean code (e.g. misleading Vector<T> v = 5)
    explicit Vector(int length) : length(length), data(new T[length]()) {}

    // Uninitialized list constructor
    Vector(std::initializer_list<T> list) : length(list.size()), data(new T[length]()) {
        std::uninitialized_copy(list.begin(), list.end(), data);
    }

    // Copy constructor
    Vector(const Vector& other) : length(other.length), data(new T[length]()) {
        for (int i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }

    // Move constructor
    Vector(Vector &&other) noexcept : length(other.length) {
        data = other.data;
        other.data = nullptr;
        other.length = 0;
    }

    /** Operators **/
    auto operator+(const Vector<T> &other) const {
        if (this->length != other.length) {
            std::cerr << "Error: the two vector dimensions must be equal." << std::endl;
            throw std::exception();
        }

        Vector<T> sum = Vector<T>(length);
        for (int i = 0; i < length; ++i) {
            sum.data[i] = this->data[i] + other.data[i];
        }
        return sum;
    }

    auto operator-(const Vector<T> &other) const {
        if (this->length != other.length) {
            std::cerr << "Error: the two vector dimensions must be equal." << std::endl;
            throw std::exception();
        }

        Vector<T> diff = Vector<T>(length);
        for (int i = 0; i < length; ++i) {
            diff.data[i] = this->data[i] - other.data[i];
        }
        return diff;
    }

    Vector<T> &operator+=(const Vector<T> &other) {
        if (this->length != other.length) {
            std::cerr << "Error: the two vector dimensions must be equal." << std::endl;
            throw std::exception();
        }

        for (int i = 0; i < length; ++i) {
            data[i] += other.data[i];
        }

        return *this;
    }

    Vector<T> &operator-=(const Vector<T> &other) {
        if (this->length != other.length) {
            std::cerr << "Error: the two vector dimensions must be equal." << std::endl;
            throw std::exception();
        }

        for (int i = 0; i < length; ++i) {
            data[i] -= other.data[i];
        }

        return *this;
    }

    // Copy assignment
    Vector<T> &operator=(const Vector<T> &other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new T[length]();
            for (int i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    // Move assignment
    Vector<T> &operator=(Vector<T> &&other) noexcept {
        delete[] data;
        length = other.length;
        data = other.data;
        other.length = 0;
        other.data = nullptr;

        return *this;
    }

    /** Iterator methods (simple) **/
    T* begin() const {
        return data;
    }

    T* end() const {
        return data + length;
    }

    /** Destructor **/
    virtual ~Vector<T>() {
        delete[] data;
        data = nullptr;
        length = 0;
    }

};

/** Mixed operators **/
template<typename T>
Vector<T> operator*(const T& val, const Vector<T>& rhs) {
    Vector<T> out = Vector<T>(rhs.length);
    for (int i = 0; i < rhs.length; ++i) {
        out.data[i] = rhs.data[i] * val;
    }
    return out;
}
template<typename T>
inline Vector<T> operator*(const Vector<T>& lhs, const T& val) {
    return operator*(val, lhs);
}

template<typename T>
T dot(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.length != rhs.length) {
        std::cerr << "Error: the two vector dimensions must be equal." << std::endl;
        throw std::exception();
    }

    T sum = 0;
    for (int i = 0; i < lhs.length; ++i) {
        sum += lhs.data[i] * rhs.data[i];
    }
    return sum;
}

#endif //HEAT_EQUATION_VECTOR_H
