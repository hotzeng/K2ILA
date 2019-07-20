auto instr = model.NewInstr("btq_r64_r64");
instr.SetUpdate(CF, lshr(0, 0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("btq_r64_r64");
