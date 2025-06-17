#include <Eigen/Core>
#include <cstring>  // for memcpy
#include <cstdint>
#include <cstdlib>
#include <iostream>        // for debug printing
#include <fstream>            // for file logging
using namespace std;
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
void mat44_diag_add_one(const uint32_t* mat, uint32_t* ou) {
    float* mat_fi = (float*)std::malloc(16*sizeof(uint32_t));
    float* mat_fo = (float*)std::malloc(16*sizeof(uint32_t));
    
    uint32_mat44_2_float_mat44(mat, mat_fi);
    transform_function(mat_fi, mat_fo);
    float_mat44_2_uint32_mat44(mat_fo, ou);
    free(mat_fi);
    free(mat_fo);
}
}

union Converter {
    uint32_t u;
    float    f;
};

extern "C" {
  // 输入：v_in_u (3×1 uint32_t 表示浮点位)；输出：M_out_u (4×4 uint32_t 表示浮点位)
  void vec2mat_dpi(
      const uint32_t* v_in_u,
      uint32_t*       M_out_u
  ) {
    // 打开日志文件
    static std::ofstream log_file("dpi_log.txt", std::ios::app);
    if (!log_file.is_open()) return;

    // 分配浮点输入向量
    float v_f[3];
    log_file << "[DPI] Received input bits:";
    for (int i = 0; i < 3; ++i) {
        Converter c; c.u = v_in_u[i];
        v_f[i] = c.f;
        log_file << " v_f[" << i << "]=" << v_f[i]
                 << "(0x" << std::hex << v_in_u[i] << std::dec << ")";
    }
    log_file << std::endl;

    // 映射为 Eigen 向量
    Map<const Matrix<float,3,1>> vec(v_f);
    // 调用转换函数
    Matrix<float,4,4> M = vecToMat(vec);

    // 调试：打印输出矩阵内容到文件
    log_file << "[DPI] Computed 4x4 matrix:" << std::endl;
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            log_file << M(r,c) << " ";
        }
        log_file << std::endl;
    }

    // 转换并拷贝输出
    for (int i = 0; i < 16; ++i) {
        Converter c; c.f = M.data()[i];
        M_out_u[i] = c.u;
    }
    log_file << "[DPI] Returning output bits." << std::endl;
  }
}
