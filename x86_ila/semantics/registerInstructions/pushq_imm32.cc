auto instr = model.NewInstr("pushq_imm32");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("pushq_imm32");
