module ESTOP #(
    parameter int MAX_LOST_PACKETS = 5,
    parameter int VALID_PACKET_THRESHOLD = 100,
    parameter int VALID_FRAME_TIMEOUT_US = 20000

) (
    input CLK,
    input data_rdy_i,
    input [31:0] decoded_data_i,
    output ESTOP_N
);

    logic [31:0] decoded_data;
    logic [31:0] previous_counter;
    logic [32:0] diff;
    logic [24:0] timeout_counter;

    logic [15:0] valid_packet_counter;
    logic [15:0] lost_packet_counter;

    logic estop = 1'b1;
    logic blah;

    always_ff @(posedge CLK) begin
        if (data_rdy_i) begin
            decoded_data <= decoded_data_i;
        end
    end

    always_comb begin
        diff = (decoded_data[31:0] - previous_counter[31:0] + 33'h100000000) % 33'h100000000;
    end

    always_ff @(posedge CLK) begin
        timeout_counter <= timeout_counter + 1;
        if (timeout_counter >= VALID_FRAME_TIMEOUT_US * 12) begin
            valid_packet_counter <= 16'b0;
            estop <= 1'b1;
            timeout_counter <= 0;
        end
        if (data_rdy_i) begin
            if(estop == 1'b1)begin  
                if(diff > 1'b0 && diff <= MAX_LOST_PACKETS) begin
                    valid_packet_counter <= valid_packet_counter + 1;
                    timeout_counter <= 16'b0;
                    if(valid_packet_counter >= VALID_PACKET_THRESHOLD) begin
                        estop <= 1'b0;
                        valid_packet_counter <= 16'b0;
                    end
                end else begin
                    valid_packet_counter <= 16'b0;
                end

                previous_counter <= decoded_data[31:0];
            end else begin  
                if(diff > 1'b0 && diff <= MAX_LOST_PACKETS) begin
                    timeout_counter <= 16'b0;
                    lost_packet_counter <= 16'b0;
                    previous_counter <= decoded_data[31:0];
                end else begin
                    lost_packet_counter <= lost_packet_counter + 1;
                    if(lost_packet_counter > MAX_LOST_PACKETS) begin
                        estop <= 1'b1;
                        lost_packet_counter <= 16'b0;
                    end
                end
            end
        end
    end

    assign ESTOP_N = ~estop;
endmodule