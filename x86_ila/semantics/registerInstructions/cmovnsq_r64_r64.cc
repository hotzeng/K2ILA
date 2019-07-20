auto instr = model.NewInstr("cmovnsq_r64_r64");
UPDATE_R(R2, Ite( ~ ((SF) == (BvConst(1, 1))), R1, R2));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmovnsq_r64_r64");
