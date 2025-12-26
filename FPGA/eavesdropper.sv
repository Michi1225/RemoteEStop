//------------------------------------------------------------------
//-- Blinking LED
//-- The Green LED is blinking. The other LEDs are turned off
//------------------------------------------------------------------
module eavesdropper (
    input logic SPI_CLK,
    input logic SPI_DATA,
    input logic SPI_NCS,
    output LED_GRN_N,
    output LED_RED_N,
    output LED_BLU_N,
    output logic [15:0] D,
    output ESTOP_N
);
    parameter data_width = 8;
    parameter data_length = 8;

    logic       CLK;
    logic [31:0] counter;
    logic spi_data_rdy;
    logic [data_width * data_length - 1:0] spi_data_out;
    logic [31:0] feistel_data;
    logic feistel_rdy;

    oscilator osc_inst (
        .clk (CLK)
    );

    // Counter
    always_ff @(posedge CLK) begin
        counter <= counter + 1;
    end

    SPI_SLV #(
        .DATA_WIDTH (data_width),
        .DATA_LENGTH(data_length)
    ) spi_slave_inst (
        .CLK        (CLK),
        .spi_ncs_i  (SPI_NCS), // Not used
        .spi_clk_i  (SPI_CLK), // Not used
        .spi_data_i (SPI_DATA), // Not used
        .data_o     (spi_data_out),
        .data_rdy_o (spi_data_rdy)      // Not used
    );

    DECODE_FEISTEL #(
        .SIZE   (32),
        .ROUNDS (4)
    ) decode_feistel_inst (
        .CLK       (CLK),
        .data_rdy_i(spi_data_rdy),
        .data_i    ({spi_data_out[23:16], spi_data_out[31:24], spi_data_out[39:32], spi_data_out[47:40]}),
        .data_o    (feistel_data),
        .ready_o   (feistel_rdy)
    );
    assign D = feistel_data[31:16];

    ESTOP #(
        .MAX_LOST_PACKETS        (5),
        .VALID_PACKET_THRESHOLD  (100),
        .VALID_FRAME_TIMEOUT_US  (20000)
    ) estop_inst (
        .CLK            (CLK),
        .data_rdy_i     (feistel_rdy),
        .decoded_data_i (feistel_data),
        .ESTOP_N        (ESTOP_N)
    );

    // assign LED_BLU_N = counter[23];
    // assign LED_RED_N = ~counter[23]; // Off

      SB_RGBA_DRV #(
      .CURRENT_MODE("0b1"),  // "0b0" -> full current, "0b1" -> half current.
      .RGB0_CURRENT("0b000001"),
      .RGB1_CURRENT("0b000001"),
      .RGB2_CURRENT("0b000001")
  ) RGB_DRIVER (
      .RGBLEDEN(1'b1),
      .RGB0PWM (1'b0),  // BLUE led input.
      .RGB1PWM (ESTOP_N),     // GREEN led input.
      .RGB2PWM (1'b0),       // RED led input.
      .CURREN  (1'b1),
      .RGB0    (LED_BLU_N),            // Current regulated output to BLUE led.
      .RGB1    (LED_GRN_N),            // Current regulated output to GREEN led.
      .RGB2    (LED_RED_N)             // Current regulated output to RED led.
  );


endmodule
