auto instr = model.NewInstr("idivq_r64");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("idivq_r64");
