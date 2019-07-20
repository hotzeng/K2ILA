auto instr = model.NewInstr("xchgq_r64_rax");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("xchgq_r64_rax");
