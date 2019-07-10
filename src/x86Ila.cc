#include <string>

#include <ilang/ila/instr_lvl_abs.h>
#include <ilang/ilang++.h>

#include "helpers.hpp"
#include "encoding.hpp"

using namespace ilang;

#include "x86Ila.hpp"

void x86ILA_user::UpdateGPR(InstrRef& inst, const ExprRef& idxBits, 
                            const ExprRef& val) {
  for (int idx = 0; idx < GPR_NUM; idx++) {
//need to know how the GPR are encoded in x85!
    
    inst.SetUpdate(GPR[idx], Ite(idxBits == BvConst(idx, 5), val, GPR[idx]));
  }
}


