// gaussian_elimination.cpp
#include "gaussian_elimination.hpp"
#include <iostream>
using namespace Eigen;

Matrix<float,4,4> vecToMat(
    const Matrix<float,3,1>& v_in
) {
    // 构建 4×4 单位矩阵
    Matrix<float,4,4> M = Matrix<float,4,4>::Identity();
    // 将向量 v_in 复制到最后一列的前 3 行
    M.template block<3,1>(0,3) = v_in;
    return M;
}

Matrix<float,4,4> transformFunction(
    const Matrix<float,4,4>& M_in
) {
    // 示例实现：对角元素加 1，其余保持不变
    Matrix<float,4,4> M_out = M_in;
    for (int i = 0; i < 4; ++i) {
        M_out(i,i) += 1.0f;
    }
    return M_out;
}