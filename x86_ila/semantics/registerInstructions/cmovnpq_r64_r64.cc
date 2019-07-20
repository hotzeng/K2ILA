auto instr = model.NewInstr("cmovnpq_r64_r64");
UPDATE_R(R2, Ite( ~ ((PF) == (BvConst(1, 1))), R1, R2));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmovnpq_r64_r64");
