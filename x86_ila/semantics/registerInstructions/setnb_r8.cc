auto instr = model.NewInstr("setnb_r8");
UPDATE_R(R1, Concat(R1(63, 8), Ite(~ ((CF) == (BvConst(1, 1))), bv(1), bv(0))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("setnb_r8");
