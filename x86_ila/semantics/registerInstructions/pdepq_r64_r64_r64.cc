auto instr = model.NewInstr("pdepq_r64_r64_r64");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("pdepq_r64_r64_r64");
