auto instr = model.NewInstr("xchgq_r64_r64");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("xchgq_r64_r64");
