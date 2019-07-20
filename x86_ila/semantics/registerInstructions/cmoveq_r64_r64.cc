auto instr = model.NewInstr("cmoveq_r64_r64");
UPDATE_R(R2, Ite( (ZF) == (BvConst(1, 1)), R1, R2));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmoveq_r64_r64");
