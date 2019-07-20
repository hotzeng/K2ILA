auto instr = model.NewInstr("movq_r64_r64");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("movq_r64_r64");
