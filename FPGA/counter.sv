module counter (
    input logic CLK,
    input logic cmd,
    output logic [4:0] count
);
  initial begin
    count = 5'b00000;
  end

  always_ff @(posedge cmd) begin
    count <= count + 1;
  end

endmodule
