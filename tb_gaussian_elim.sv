module tb_gauss;
  // 使用 uint32_t 承载每个浮点值的位模式，注意先声明元素位宽，然后声明数组维度（unpacked）
  typedef bit [31:0] elem_t;
  typedef elem_t vec3_u_t  [3];  // 3×1 向量
  typedef elem_t mat4_u_t  [4][4]; // 4×4 矩阵
  typedef bit[3:0][3:0][31:0] packed_2d_t;

  vec3_u_t vec_u;
  mat4_u_t mat_u;

  packed_2d_t a,b;

  import "DPI-C" function void vec2mat_dpi(
    input  vec3_u_t  vec_u,
    output mat4_u_t  mat_u
  );
  
import "DPI-C" function mat44_diag_add_one(input packed_2d_t a, output packed_2d_t b);

  function void randomize_vec(output vec3_u_t v);
    int i;
    for (i = 0; i < 3; i++) begin
      //// 直接随机位模式或从合理浮点生成后位转换
      //shortreal tmp = $urandom_range(0,100)/10.0;
      //v[i] = $realtobits(tmp);
      v[i] = $urandom();
      $display("v[%0d] = %f", i, $bitstoshortreal(v[i]));
    end
  endfunction

  initial begin
    int i,j;
    int di,dj;

    randomize_vec(vec_u);
    // Debug: 打印向量位模式
    $display("[SV] Input vector bits:");
    foreach (vec_u[i]) $display("vec_u[%0d] = 0x%h", i, vec_u[i]);

    vec2mat_dpi(vec_u, mat_u);
    // Debug: 打印输出矩阵位模式
    $display("[SV] Received matrix bits:");
    for (di = 0; di < 4; di++) begin
      for (dj = 0; dj < 4; dj++) begin
        $write("0x%h ", mat_u[di][dj]);
      end
      $display("");
    end
    $display("Resulting 4x4 matrix (float):");
    $display("Resulting 4x4 matrix:");
    for (i = 0; i < 4; i++) begin
      for (j = 0; j < 4; j++) begin
        //// 从位模式转换为 shortreal 输出
        //shortreal val = $bitstoshortreal(mat_u[i][j]);
        //$write("%f ", val);
        $display("mat_u[%0d][%0d] = %f", i, j, $bitstoshortreal(mat_u[i][j]));
      end
      $display("");
    end

    foreach (a[i,j]) begin
        a[i][j] = $urandom();
        $display("a[%0d][%0d] = %f", i, j, $bitstoshortreal(a[i][j]));
    end
    mat44_diag_add_one(a, b);
    $display("Resulting 4x4 matrix b:");
    foreach (b[i,j]) $display("b[%0d][%0d] = %f", i, j, $bitstoshortreal(b[i][j]));
    $finish;
  end
endmodule