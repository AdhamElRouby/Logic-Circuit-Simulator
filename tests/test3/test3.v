module test_circuit_3 (
    input A, B, C, output Y
);

    wire w1, w2, w3;

    and #(200) g0(w1, A, B);
    and #(200) g1(w2, B, C);
    and #(200) g2(w3, A, C);
    or  #(300) g3(Y, w1, w2, w3);

endmodule
