// gaussian_elimination.hpp
#ifndef GAUSSIAN_ELIMINATION_HPP
#define GAUSSIAN_ELIMINATION_HPP

#include <Eigen/Dense>
Eigen::VectorXd gaussianElimination(
    const Eigen::MatrixXd& A,
    const Eigen::VectorXd& b
);

#endif // GAUSSIAN_ELIMINATION_HPP