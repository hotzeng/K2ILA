auto instr = model.NewInstr("btw_r16_r16");
instr.SetUpdate(CF, lshr(48, 48));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("btw_r16_r16");
