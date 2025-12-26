`timescale 1ns/1ps

module decodeFeistel_tb;

    // Parameters (match your module)
    parameter SIZE     = 32;
    parameter ROUNDS   = 4;
    parameter KEY_SIZE = SIZE/2;

    // Testbench signals
    logic CLK;
    logic data_rdy_i;
    logic [SIZE-1:0] data_i;
    logic [SIZE-1:0] data_o;

    // Instantiate the DUT
    DECODE_FEISTEL #(
        .SIZE(SIZE),
        .ROUNDS(ROUNDS),
        .KEY_SIZE(KEY_SIZE)
    ) dut (
        .CLK(CLK),
        .data_rdy_i(data_rdy_i),
        .data_i(data_i),
        .data_o(data_o)
    );

    // Clock generation
    initial CLK = 0;
    always #5 CLK = ~CLK; // 100 MHz simulation clock

    // File handles
    integer infile, outfile;
    integer r;

    initial begin
        // Open input and output files
        infile  = $fopen("decode_input.txt", "r");
        if (infile == 0) begin
            $display("ERROR: cannot open input file");
            $finish;
        end

        outfile = $fopen("decode_output.txt", "w");
        if (outfile == 0) begin
            $display("ERROR: cannot open output file");
            $finish;
        end

        data_rdy_i = 0;

        // Read input file line by line
        while (!$feof(infile)) begin
            r = $fscanf(infile, "%h\n", data_i); // read 32-bit hex input

            // Pulse data_rdy_i
            data_rdy_i = 1;
            @(posedge CLK);
            data_rdy_i = 0;

            // Wait one cycle for output to register
            @(posedge CLK);

            // Write output to file in hex
            $fwrite(outfile, "%08h\n", data_o);
        end

        $fclose(infile);
        $fclose(outfile);

        $display("Simulation complete, outputs written to decode_output.txt");
        $finish;
    end

endmodule
