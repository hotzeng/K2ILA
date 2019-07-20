auto instr = model.NewInstr("cmovngeq_r64_r64");
UPDATE_R(R2, Ite( ~ (((SF) == (BvConst(1, 1))) == ((OF) == (BvConst(1, 1)))), R1, R2));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmovngeq_r64_r64");
