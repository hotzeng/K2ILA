auto instr = model.NewInstr("xchgq_rax_r64");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("xchgq_rax_r64");
