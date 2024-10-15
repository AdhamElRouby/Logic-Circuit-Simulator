module test_circuit_1 (
    input A, B, C, output Y
);

    wire w1, w2, w3;

    not #(100) g0(w1, C);
    or #(200) g1(w2, A, w1);
    or #(200) g2(w3, B, C);
    and #(300) g3(Y, w2, w3);

endmodule
