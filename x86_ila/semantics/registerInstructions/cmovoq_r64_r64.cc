auto instr = model.NewInstr("cmovoq_r64_r64");
UPDATE_R(R2, Ite( (OF) == (BvConst(1, 1)), R1, R2));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmovoq_r64_r64");
