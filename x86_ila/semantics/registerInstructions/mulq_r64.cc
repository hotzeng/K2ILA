auto instr = model.NewInstr("mulq_r64");
UPDATE_R(RAX, mul(-1, -64));
UPDATE_R(RDX, mul(63, 0));
instr.SetUpdate(CF, Ite( ~ ((mul(63, 0)) == (BvConst(0, 64))), bv(1), bv(0)));
instr.SetUpdate(OF, Ite( ~ ((mul(63, 0)) == (BvConst(0, 64))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("mulq_r64");
