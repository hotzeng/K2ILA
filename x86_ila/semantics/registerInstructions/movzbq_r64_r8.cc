auto instr = model.NewInstr("movzbq_r64_r8");
UPDATE_R(R2, Concat(bv(0), R1(7, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("movzbq_r64_r8");
