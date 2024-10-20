module c4 (i2, i1, i0, o);
    
    input i2;
    input i1;
    input i0;
    output o;

    wire w1;
    wire w0;
    
    xor #(1) g1 (w1,i2,i1);
    not #(1) g2 (w0,i0);
    and #(1) g3 (o,w1,w0);

endmodule
