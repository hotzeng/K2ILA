auto instr = model.NewInstr("mulw_r16");
UPDATE_R(RAX, Concat(rax(63, 16), mul(47, 32)));
UPDATE_R(RDX, Concat(rdx(63, 16), mul(63, 48)));
instr.SetUpdate(CF, Ite( ~ ((mul(63, 48)) == (BvConst(0, 16))), bv(1), bv(0)));
instr.SetUpdate(OF, Ite( ~ ((mul(63, 48)) == (BvConst(0, 16))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("mulw_r16");
