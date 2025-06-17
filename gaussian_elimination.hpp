// gaussian_elimination.hpp
#ifndef GAUSSIAN_ELIMINATION_HPP
#define GAUSSIAN_ELIMINATION_HPP

#include <Eigen/Dense>
#include <Eigen/Core>

//// 输入：3×1 向量 b；输出：4×4 矩阵 M
//Eigen::Matrix<float,4,4> transformFunction(
//    const Eigen::Matrix<float,3,1>& b
//);
// 输入：4×4 矩阵 M_in；输出：4×4 矩阵 M_out
Eigen::Matrix<float,4,4> transformFunction(
    const Eigen::Matrix<float,4,4>& M_in
);

#endif // GAUSSIAN_ELIMINATION_HPP
