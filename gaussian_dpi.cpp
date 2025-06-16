#include <Eigen/Dense>
#include "gaussian_elimination.hpp"
using namespace Eigen;

extern "C" {
  // 输入：A（n×n 行优先），b（长度 n）；输出：x（长度 n）
  void gaussian_elimination_dpi(
      const double* A,
      const double* b,
      double* x,
      int n
  ) {
    Map<const MatrixXd> matA(A, n, n);
    Map<const VectorXd> vecb(b, n);
    VectorXd result = gaussianElimination(matA, vecb);
    for (int i = 0; i < n; ++i)
      x[i] = result[i];
  }
}