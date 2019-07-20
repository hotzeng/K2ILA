auto instr = model.NewInstr("roll_r32_one");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("roll_r32_one");
