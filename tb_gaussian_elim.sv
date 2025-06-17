module tb_gauss;
    typedef bit[3:0][3:0][31:0] packed_2d_t;

    packed_2d_t a,b;

    import "DPI-C" function mat44_inverse(input packed_2d_t a, output packed_2d_t b);

  initial begin
    foreach (a[i,j]) begin
        a[i][j] = $urandom();
        $display("a[%0d][%0d] = %f", i, j, $bitstoshortreal(a[i][j]));
    end
    mat44_inverse(a, b);
    $display("Resulting 4x4 matrix b:");
    foreach (b[i,j]) $display("b[%0d][%0d] = %f", i, j, $bitstoshortreal(b[i][j]));
    $finish;
  end
endmodule
