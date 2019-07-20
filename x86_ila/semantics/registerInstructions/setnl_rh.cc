auto instr = model.NewInstr("setnl_rh");
UPDATE_R(R1, Concat(Concat(R1(63, 16), Ite(((SF) == (BvConst(1, 1))) == ((OF) == (BvConst(1, 1))), bv(1), bv(0))), R1(7, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("setnl_rh");
