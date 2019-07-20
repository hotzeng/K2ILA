auto instr = model.NewInstr("cmovaeq_r64_r64");
UPDATE_R(R2, Ite( ~ ((CF) == (BvConst(1, 1))), R1, R2));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmovaeq_r64_r64");
