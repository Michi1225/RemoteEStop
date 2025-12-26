module DECODE_FEISTEL #(
    parameter int SIZE     = 32,
    parameter int ROUNDS   = 4,
    parameter int KEY_SIZE = SIZE / 2
) (
    input  logic               CLK,
    input  logic               data_rdy_i,
    input  logic [SIZE-1:0]    data_i,
    output logic [SIZE-1:0]    data_o,
    output logic               ready_o
);

    // Packed keys vector
    localparam logic [KEY_SIZE*ROUNDS-1:0] KEYS = {
        16'h1234,
        16'hBEEF,
        16'hCAFE,
        16'h0BAD
    };

    logic data_rdy;
    logic [SIZE-1:0] data_buf;
    // Buffer the Input data

    always_ff @(posedge CLK) begin
        if (data_rdy_i) begin
            data_buf <= data_i;
        end 
        data_rdy <= data_rdy_i;
    end


    // Function to extract individual keys
    function logic [KEY_SIZE-1:0] get_key(input int idx);
        // rounds -idx because h1234 is MSB, i.e., used in first round
        get_key = KEYS[KEY_SIZE*(ROUNDS-idx)-1 -: KEY_SIZE];
    endfunction

    // Feistel function
    function automatic logic [KEY_SIZE-1:0] F (
        input logic [KEY_SIZE-1:0] r,
        input logic [KEY_SIZE-1:0] k
    );
        logic [KEY_SIZE-1:0] tmp;
        begin
            tmp = r + k;
            tmp = tmp ^ ((tmp << 5) | (tmp >> (11)));
            tmp = tmp ^ (tmp >> 3);
            F = tmp;
        end
    endfunction

    // Internal signals
    logic [KEY_SIZE-1:0] L_next, R_next;

    // Temporaries outside always_comb
    logic [KEY_SIZE-1:0] f_tmp, tmp_val;
    integer i;

    // Combinational Feistel decode
    always_comb begin
        L_next = data_buf[SIZE-1:KEY_SIZE];
        R_next = data_buf[KEY_SIZE-1:0];

        for (i = ROUNDS-1; i >= 0; i=i-1) begin
            f_tmp   = F(L_next, get_key(i));
            tmp_val = R_next;
            R_next  = L_next;
            L_next  = tmp_val ^ f_tmp;
        end
    end

    // this assumes a long enough clock period to compute combinational logic
    // but it is probably ok, because the time between last clock pulse and 
    // cs high is long enough to accommodate this
    
    // Register output
    always_ff @(posedge CLK) begin
        if (data_rdy) begin
            data_o <= {L_next, R_next};
            ready_o <= 1'b1;
        end else begin
            ready_o <= 1'b0;
        end
    end

endmodule
