auto instr = model.NewInstr("setne_rh");
UPDATE_R(R1, Concat(Concat(R1(63, 16), Ite(~ ((ZF) == (BvConst(1, 1))), bv(1), bv(0))), R1(7, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("setne_rh");
