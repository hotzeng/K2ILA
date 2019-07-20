auto instr = model.NewInstr("clc");
instr.SetUpdate(CF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("clc");
