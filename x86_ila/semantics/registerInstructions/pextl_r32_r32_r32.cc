auto instr = model.NewInstr("pextl_r32_r32_r32");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("pextl_r32_r32_r32");
