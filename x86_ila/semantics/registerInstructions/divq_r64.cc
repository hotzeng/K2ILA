auto instr = model.NewInstr("divq_r64");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("divq_r64");
