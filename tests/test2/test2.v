module test_circuit_2 (A, B, C, D, Y);

    input A;
    input B;
    input C;
    input D;
    output Y;

    wire [2:0] w;

    xor #(150) g0(w[0],A,B);
    xor #(150) g1(w[1],C,D);
    and #(250) g2(w[2],w[0],w[1]);
    or  #(300) g3(Y,w[2],B);

endmodule
