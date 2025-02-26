module PC #(
    DW=32

) (
    input logic             clk,
    input logic             rst,
    input logic   [DW-1:0]  PC_i,
    output logic  [DW-1:0]  PC_o
);
    
    always_ff @(posedge clk ) begin
        if (rst) PC_o<=32'b0;
        else PC_o<=PC_i;
        // $display (PC_o);
    end

endmodule 
