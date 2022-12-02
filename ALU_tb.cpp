#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"

//#include "vbuddy.cpp"     // include vbuddy code
#define MAX_SIM_CYC 1000000
#define ADDRESS_WIDTH 9
#define RAM_SZ pow(2,ADDRESS_WIDTH)

int main(int argc, char **argv, char **env) {
  int simcyc;     // simulation clock count
  int tick;       // each clk cycle has two ticks for two edges

  Verilated::commandArgs(argc, argv);
  // init top verilog instance
  Vtop* top = new Vtop;
  // init trace dump
  Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top->trace (tfp, 99);
  tfp->open ("ALU_test.vcd");

  // initialize simulation input 
  top->SrcA_i = 20;
  top->SrcB_i = 10;
  top->ALUctrl_i = 0;

  // run simulation for MAX_SIM_CYC clock cycles
  for (simcyc=0; simcyc<MAX_SIM_CYC; simcyc++) {
    // dump variables into VCD file and toggle clock
    for (tick=0; tick<2; tick++) {
      tfp->dump (2*simcyc+tick);
      top->clk = !top->clk;
      top->eval ();
    }

    //sub
    if(simcyc == 1){
      top->ALUctrl_i = 1;
    }

    //and
    if(simcyc == 2){
      top->ALUctrl_i = 2;
    }

    //or
    if(simcyc == 3){
      top->ALUctrl_i = 3;
    }

    //SLT
    if(simcyc == 4){
      top->ALUctrl_i = 5;
    }  //0
    if(simcyc == 6){
      top->SrcB_i = 30;
      top->ALUctrl_i = 5;
    } //1
    if(simcyc == 8){
      top->SrcB_i = -30;
      top->ALUctrl_i = 5;
    } // 1
    if(simcyc == 10){
      top->SrcA_i = -20;
      top->ALUctrl_i = 5;
    } // 0
    if(simcyc == 12){
      top->SrcA_i = -40;
      top->ALUctrl_i = 5;
    } //1
    if(simcyc == 14){
      top->SrcA_i = -30;
      top->ALUctrl_i = 5;
    } //0
    if(simcyc == 16){
      top->SrcA_i = 30;
      top->SrcA_i = 30;
      top->ALUctrl_i = 5;
    } //0

    //todo test edge cases

    //ULT
    if(simcyc == 18){
      top->ALUctrl_i = 6;
    }

    // either simulation finished, or 'q' is pressed
    if (Verilated::gotFinish()) 
      exit(0);
  }

  tfp->close(); 
  printf("Exiting\n");
  exit(0);
}
