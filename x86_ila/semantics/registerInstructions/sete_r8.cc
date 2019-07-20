auto instr = model.NewInstr("sete_r8");
UPDATE_R(R1, Concat(R1(63, 8), Ite((ZF) == (BvConst(1, 1)), bv(1), bv(0))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("sete_r8");
