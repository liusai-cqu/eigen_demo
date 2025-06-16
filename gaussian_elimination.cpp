// gaussian_elimination.cpp
#include "gaussian_elimination.hpp"
#include <iostream>
using namespace Eigen;

VectorXd gaussianElimination(
    const MatrixXd& A,
    const VectorXd& b
) {
    const Index n = A.rows();
    MatrixXd aug(n, n+1);
    aug << A, b;
    for (Index k = 0; k < n; ++k) {
        if (aug(k,k) == 0) {
            std::cerr << "Zero pivot!" << std::endl;
            exit(EXIT_FAILURE);
        }
        for (Index i = k+1; i < n; ++i) {
            double f = aug(i,k)/aug(k,k);
            for (Index j = k; j <= n; ++j)
                aug(i,j) -= f*aug(k,j);
        }
    }
    VectorXd x(n);
    for (Index i = n-1; i >= 0; --i) {
        x(i) = aug(i,n);
        for (Index j = i+1; j < n; ++j)
            x(i) -= aug(i,j)*x(j);
        x(i) /= aug(i,i);
    }
    return x;
}