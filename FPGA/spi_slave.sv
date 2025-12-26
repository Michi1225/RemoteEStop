module SPI_SLV #(
    parameter DATA_WIDTH  = 8,
    parameter DATA_LENGTH = 1

) (
    input logic CLK,
    input logic spi_ncs_i,
    input logic spi_clk_i,
    input logic spi_data_i,
    output logic [DATA_WIDTH * DATA_LENGTH - 1:0] data_o,
    output logic data_rdy_o
);

  logic [DATA_WIDTH * DATA_LENGTH - 1:0] data_buffer;

  logic [7:0] bit_count;

  // temporary signals for sychronization and metastability reduction
  logic spi_ncs_tmp;
  logic spi_clk_tmp;
  logic spi_data_tmp;

  // synchronized signals
  logic spi_ncs;
  logic spi_clk;
  logic spi_data;


  // Synchronize inputs & imporve metastability
  always_ff @(posedge CLK) begin
    spi_ncs_tmp <= spi_ncs_i;
    spi_clk_tmp <= spi_clk_i;
    spi_data_tmp <= spi_data_i;

    spi_ncs <= spi_ncs_tmp;
    spi_clk <= spi_clk_tmp;
    spi_data <= spi_data_tmp;
  end

  // positive edge detection for SPI clock
  logic spi_clk_dly;
  logic spi_clk_posedge;
  always_ff @(posedge CLK) begin
    spi_clk_dly <= spi_clk;
    spi_clk_posedge <= (spi_clk == 1'b1) && (spi_clk_dly == 1'b0);
  end


  // SPI data reception

  always_ff @(posedge CLK) begin
    if (spi_ncs == 1'b1) begin
      if (bit_count == DATA_WIDTH * DATA_LENGTH) begin
        data_o <= data_buffer;
        data_rdy_o <= 1'b1;
      end else begin
        data_rdy_o <= 1'b0;
      end
      bit_count   <= '0;
      data_buffer <= '0;
    end else begin
      if (spi_clk_posedge) begin
        data_buffer <= {data_buffer[DATA_WIDTH*DATA_LENGTH-2:0], spi_data};
        bit_count   <= bit_count + 1;
      end

      if(data_rdy_o) begin
        data_rdy_o <= 1'b0;
      end

    end

  end



endmodule
