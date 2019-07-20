auto instr = model.NewInstr("mull_r32");
UPDATE_R(RAX, Concat(bv(0), mul(31, 0)));
UPDATE_R(RDX, Concat(bv(0), mul(63, 32)));
instr.SetUpdate(CF, Ite( ~ ((mul(63, 32)) == (BvConst(0, 32))), bv(1), bv(0)));
instr.SetUpdate(OF, Ite( ~ ((mul(63, 32)) == (BvConst(0, 32))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("mull_r32");
