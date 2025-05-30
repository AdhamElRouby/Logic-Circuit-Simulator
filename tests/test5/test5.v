module c5(i2, i1, i0, o);
    
    input i2;
    input i1;
    input i0;
    output o;

    wire w;

    or #(1) g1(w,i1,i0);
    xnor #(1) g2(o,i2,w);

endmodule
