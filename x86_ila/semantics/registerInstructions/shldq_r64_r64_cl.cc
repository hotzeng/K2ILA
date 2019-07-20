auto instr = model.NewInstr("shldq_r64_r64_cl");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("shldq_r64_r64_cl");
