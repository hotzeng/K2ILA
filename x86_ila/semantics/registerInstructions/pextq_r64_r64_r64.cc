auto instr = model.NewInstr("pextq_r64_r64_r64");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("pextq_r64_r64_r64");
