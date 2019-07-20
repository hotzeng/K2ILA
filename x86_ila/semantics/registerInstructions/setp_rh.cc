auto instr = model.NewInstr("setp_rh");
UPDATE_R(R1, Concat(Concat(R1(63, 16), Ite((PF) == (BvConst(1, 1)), bv(1), bv(0))), R1(7, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("setp_rh");
