#include <string>

#include <ilang/ila/instr_lvl_abs.h>
#include <ilang/ilang++.h>

#include "helpers.hpp"
#include "encoding.hpp"

using namespace ilang;

#include "x86Ila.hpp"

// idxBits can be 3 bits or 4 bits(64-bit mode),
// so need to check is long mode or not
void x86ILA_user::UpdateGPR(InstrRef& inst, const ExprRef& idxBits, 
                            const ExprRef& val) {
  for (int idx = 0; idx < GPR_NUM; idx++) {
    inst.SetUpdate(GPR[idx],  Ite(long_mode == BoolConst(true), 
                                Ite(idxBits == BvConst(idx, 4), val, GPR[idx]),
                                Ite(idxBits == BvConst(idx, 3), val, GPR[idx])
                              )
    );
  }
}


ExprRef x86ILA_user::indexIntoGPR(const ExprRef& idxBits) {
  auto expr = bv(0) //FIXME: what is the default value?
  for (int idx = 0; idx < GPR_NUM; idx++) {
    expr =  Ite(long_mode == BoolConst(true),
              Ite(idxBits == BvConst(idx, 4), GPR[idx], expr),
              Ite(idxBits == BvConst(idx, 3), GPR[idx], expr)
            );
  }
  return expr;
}


// Initialize x86ILA_user object
x86ILA_user::x86ILA_user(int pc_init_val)
  : model(InstrLvlAbs::New("x86-64")),
    // TODO: decoding part, to assign prefix, opcode, ModRM,
    // SIB, immediate, displacement

{
  // initialize 16 GPR
  for (int i = 0; i < GPR_NUM; i++)
    GPR.push_back(model.NewBvState("r" + std::to_string), RLEN);
  // TODO: check EIP is alighed??
  model.AddInit (IP == Ite(long_mode == BoolConst(true)),
                        BvConst(pc_init_val, RLEN),
                        BvConst(pc_init_val, ELEN)
                );
}


void x86ILA_user::addInstructions() {
  // TODO: incorporating translated ILA models later 
}
