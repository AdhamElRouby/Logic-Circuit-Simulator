module test_circuit_6 (A)

    input A;
    wire B;

    xor #(100) g1(B,A,B);


endmodule
