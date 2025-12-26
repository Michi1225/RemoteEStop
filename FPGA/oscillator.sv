
module oscilator (
    output clk
);
    logic clk_internal;
    logic [2:0] clk_cntr;
  SB_HFOSC interal_osc (
      .CLKHFPU(1'b1),
      .CLKHFEN(1'b1),
      .CLKHF  (clk_internal),

      // Unused
      .TRIM0(),
      .TRIM1(),
      .TRIM2(),
      .TRIM3(),
      .TRIM4(),
      .TRIM5(),
      .TRIM6(),
      .TRIM7(),
      .TRIM8(),
      .TRIM9()
  );

  always_ff @(posedge clk_internal) begin
    clk_cntr <= clk_cntr + 1;
  end

    assign clk = clk_cntr[2]; // 12MHz from 48MHz




endmodule