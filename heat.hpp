#ifndef HEAT_EQUATION_HEAT_HPP
#define HEAT_EQUATION_HEAT_HPP

#include <cmath>
#include "cg.hpp"

// Create templated class Heat with n dimensions and T type of elements
template<int n, typename T>
class Heat {
public:
    const T alpha;
    const int m;
    const T dt;

    Matrix<T> M;

    Heat(T alpha, int m, T dt) : alpha(alpha), m(m), dt(dt), M(Matrix<T>(pow(m, n), pow(m, n))) {
        static_assert(n >= 1); // don't let n <= 0 be compiled

        T dx = 1 / ((T) (m + 1));
        T coeff = alpha * dt / pow(dx, 2);

        idx size = (idx) pow(m, n);

        idx j;
        for (idx i = 0; i < size; ++i) {
            M[{i, i}] = 1 + 2 * coeff * n; // identity matrix + case d_ijk with i = j
            for (idx k = 0; k < n; ++k) {
                int v = pow(m, k);

                j = i + v; // only consider right neighbours (the symmetry will take care of the left neighbours)
                if (j < size && (i / ((int) v)) % m != m - 1) { // check explained in report
                    M[{i, j}] = -coeff; // the cycle will only hit a particular (i, j) pair once
                    M[{j, i}] = -coeff; // build lower triangle of the symmetric matrix
                }
            }
        }
    }

    // Return straightforward solution for n = 1
    // std::enable_if is required as we are specializing a function inside a templated class in n but not in T
    template<typename U=T>
    typename std::enable_if<n == 1, Vector<U>>::type
    exact(const T& t) const {
        Vector<T> vec = Vector<T>(m);
        double dx = 1 / ((double) (m + 1));

        for (int idx = 0; idx < m; ++idx) {
            double x = (idx + 1) * dx;
            // single component e^(-pi^2 * alpha * t) * sin(pi * x)
            vec.data[idx] = exp(-pow(M_PI, 2) * alpha * t) * sin(M_PI * x);
        }

        return vec;
    }

    // Recurse to n - 1 for n >= 1 and add e^(-pi^2 * alpha * t) * sin(pi * x) component every time
    template<typename U=T>
    typename std::enable_if<n != 1, Vector<U>>::type
    exact(const T& t) const {
        Heat<n - 1, T> prev = Heat<n - 1, T>(alpha, m, dt);
        Vector<T> vec = prev.exact(t);
        Vector<T> final = Vector<T>(pow(m, n));
        double dx = 1 / ((double) (m + 1));

        for (int vIdx = 0; vIdx < vec.length; ++vIdx) {
            for (int iIdx = 0; iIdx < m; ++iIdx) {
                double x = (iIdx + 1) * dx;

                final.data[vIdx * m + iIdx] = vec.data[vIdx] * exp(-pow(M_PI, 2) * alpha * t) * sin(M_PI * x);
            }
        }

        return final;
    }

    Vector<T> solve(const T& t) const {
        Vector<T> x = exact(0); // we find the initial condition by evaluating exact() in t = 0 to avoid code complexity

        for (T tt = 0; tt < t; tt += this->dt) {
            // cg is evaluated N times such that N*dt is close to t.
            // At every iteration, the initial guess for x is taken from the previous iteration's result, which is
            // expected to be close to the next iteration's solution, thus reducing computation time.
            int k = cg(M, x, x, (T) 1e-6, 50);
            if (k == -1) {
                std::cout << "Warning: computation exceeded 50 iterations without converging (tt = " << tt << "s)"
                          << std::endl;
            }
        }

        return x;
    }

    /** Destructor **/
    virtual ~Heat() = default;
};

#endif // HEAT_EQUATION_HEAT_HPP