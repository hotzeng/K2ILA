auto instr = model.NewInstr("pdepl_r32_r32_r32");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("pdepl_r32_r32_r32");
