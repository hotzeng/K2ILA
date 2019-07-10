// 05-26-2019
// Author: yuzeng

#ifndef __RISCV_ILA_HPP__
#define __RISCV_ILA_HPP__

#include <ilang/ilang++.h>

namespace ilang {
   
class x86ILA_user {

  Ila model;
  
  ExprRef EIP;
  // physical memory, size of 2^36
  ExprRef physicalMem;

  std::vector<ExprRef> GPR;
  std::vector<ExprRef> SegReg; //segment registers
  std::vector<ExprRef> EFLAGS;

  // at leat 3 working modes, default to be protected
  ExprRef work_mode;

  // read one byte of instruction each time
  std::vector<ExprRef> inst_byte;
  int inst_no;
  ExprRef prefix_finished;
  ExprRef displacement_finished;
  ExprRef immediate_finished;
  // More regs for extensions...


  // encodings
  /// prefxes
  ExprRef pfx_rex;
  ExprRef pfx_seg;
  ExprRef pfx_opr;
  ExprRef pfx_adr;
  ExprRef pfx_lock;
  ExprRef pfx_str;
  ExprRef pfx_rep;
  ExprRef pfx_repe;
  ExprRef pfx_repne;


  ExprRef opcode;
  ExprRef encode_mod;
  ExprRef regop;  // Reg/Opcode
  ExprRef rm;     // R/M
  ExprRef scale;
  ExprRef index;
  ExprRef base;
  ExprRef displacement;
  ExprRef immediate;


protected:
  ExprRef indexIntoGPR(const ExprRef& idxBits);
  void UpdateGPR(InstrRef& inst, const ExprRef& idxBits, const ExprRef& val);


public:
  x86ILA_user(int eip_init_val);
  void addInstructions();

  virtual ExprRef FetchFromMem(const ExprRef& m, const ExprRef& addr) {
    return Load(m, addr);
  }
  virtual ExprRef LoadFromMem(const ExprRef& m, const ExprRef& addr) {
    return Load(m, addr);
  }
  virtual ExprRef StoreToMem(const ExprRef& m, const ExprRef& addr,
                             const ExprRef& data) {
    return Store(m, addr, data);
  }

};

class x86_machine : public x86_user {};

}; // namespace ilang

#endif
