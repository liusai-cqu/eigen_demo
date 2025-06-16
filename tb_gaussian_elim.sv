module tb_gauss;
    // 参数定义
    parameter int N = 3;

    // 测试矩阵与向量
    real A [N][N] = '{ '{1.0, 2.0, 3.0},
                       '{4.0, 5.0, 6.0},
                       '{7.0, 8.0, 10.0} };
    real b [N]     = '{6.0, 15.0, 25.0};
    real x [N];     // 输出解

    // DPI-C 导入声明
    import "DPI-C" function void gaussian_elimination_dpi(
        input real A[][],     // 二维数组自动传递行优先
        input real b[],        // 一维输入向量
        output real x[],       // 一维输出向量
        input int n            // 矩阵大小
    );

    initial begin
        // 调用 DPI 接口
        gaussian_elimination_dpi(A, b, x, N);

        // 打印结果
        $display("Solution x:");
        foreach (x[i]) $display("x[%0d] = %0f", i, x[i]);

        $finish;
    end
endmodule