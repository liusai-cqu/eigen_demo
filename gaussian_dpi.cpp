#include <Eigen/Core>
#include <cstring>  // for memcpy
#include <cstdlib>
#include "gaussian_elimination.hpp"
using namespace Eigen;


union converter {
    uint32_t u;
    float    f;
};

void uint32_mat44_2_float_mat44(const uint32_t *mat_ui, float* mat_fo) {
    int i,j;
    for(i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            union converter c;
            c.u = *(mat_ui+4*i+j);
            *(mat_fo+4*i+j) = c.f;
        }
    }
}

void float_mat44_2_uint32_mat44(const float *mat_fi, uint32_t* mat_uo) {
    int i,j;
    for(i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            union converter c;
            c.f = *(mat_fi+4*i+j);
            *(mat_uo+4*i+j) = c.u;
        }
    }
}

  // 输入：M_in_in (4×4)，输出：M_out_out (4×4)
  void transform_function(
      const float* M_in_in,
      float* M_out_out
  ) {
    // 映射输入 4×4 矩阵（行优先存储）
    Map<const Matrix<float,4,4>> M_in(M_in_in);
    // 调用固定维度函数
    Matrix<float,4,4> M_out = transformFunction(M_in);

    // 使用 memcpy 拷贝结果到输出数组
    std::memcpy(
      M_out_out,
      M_out.data(),
      sizeof(float) * 16
    );
  }

extern "C" {
void mat44_inverse(const uint32_t* mat, uint32_t* ou) {
    float* mat_fi = (float*)std::malloc(16*sizeof(uint32_t));
    float* mat_fo = (float*)std::malloc(16*sizeof(uint32_t));
    
    uint32_mat44_2_float_mat44(mat, mat_fi);
    transform_function(mat_fi, mat_fo);
    float_mat44_2_uint32_mat44(mat_fo, ou);
    free(mat_fi);
    free(mat_fo);
}
}

  //// 将输入数组 b_in 映射为 Eigen 向量，并返回结果到 M_out (4×4)
  //void transform_function(
  //    const float* b_in,
  //    float* M_out
  //) {
  //  // 在函数体内进行 Map 映射，确保 b_in 在运行时
  //  Eigen::Map<const Eigen::Matrix<float,3,1>> vecb(b_in);
  //  // 调用固定维度函数
  //  Eigen::Matrix<float,4,4> M = transformFunction(vecb);

  //  // 使用 memcpy 按行优先拷贝 16 个 float
  //  std::memcpy(
  //    M_out,
  //    M.data(),
  //    sizeof(float) * 16
  //  );
  //}

