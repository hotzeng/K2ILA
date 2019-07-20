auto instr = model.NewInstr("cmovpq_r64_r64");
UPDATE_R(R2, Ite( (PF) == (BvConst(1, 1)), R1, R2));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmovpq_r64_r64");
