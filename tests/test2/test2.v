module test_circuit_2 (A, B, C, D, Y);

    input A;
    input B;
    input C;
    input D;
    output Y;

    wire w1;
    wire w2;
    wire w3;

    xor #(150) g0(w1,A,B);
    xor #(150) g1(w2,C,D);
    and #(250) g2(w3,w1,w2);
    or  #(300) g3(Y,w3,B);

endmodule
