auto instr = model.NewInstr("btl_r32_r32");
instr.SetUpdate(CF, lshr(32, 32));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("btl_r32_r32");
