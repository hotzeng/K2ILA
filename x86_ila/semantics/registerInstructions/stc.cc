auto instr = model.NewInstr("stc");
instr.SetUpdate(CF, bv(1));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("stc");
