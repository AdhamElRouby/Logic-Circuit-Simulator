module c4 (input i2,i1,i0,output o);
wire w1,w0;
xor #(1)(w1,i2,i1);
not #(1)(w0,i0);
and #(1)(o,w1,w0);
endmodule 