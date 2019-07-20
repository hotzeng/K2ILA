auto instr = model.NewInstr("setnge_r8");
UPDATE_R(R1, Concat(R1(63, 8), Ite(~ (((SF) == (BvConst(1, 1))) == ((OF) == (BvConst(1, 1)))), bv(1), bv(0))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("setnge_r8");
