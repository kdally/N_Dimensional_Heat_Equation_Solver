#ifndef HEAT_EQUATION_CG_HPP
#define HEAT_EQUATION_CG_HPP

#include "matrix.hpp"

// Complex conjugate linear system solver
template<typename T>
int cg(const Matrix<T> &A, const Vector<T> &b, Vector<T> &x, const T& tol, int maxiter) {

    Vector<T> pk = b - A * x;
    Vector<T> rk(pk);

    T alphaK;

    Vector<T> old_rk;
    for (int k = 0; k < maxiter; ++k) {
        alphaK = dot(rk, rk) / dot(A * rk, rk);

        x += alphaK * pk;

        old_rk = std::move(rk); // Use move constructor to save time on copying
        rk = old_rk - alphaK * (A * pk);

        if (dot(rk, rk) < tol * tol) {
            return ++k; // should return 1 when solution is tolerable after the first iteration
        }

        pk = rk + (dot(rk, rk) / dot(old_rk, old_rk)) * pk;
    }

    if (dot(rk, rk) < tol * tol)
        return maxiter;
    else
        ~pk();
        ~rk();
        return -1;
}


#endif //HEAT_EQUATION_CG_HPP
