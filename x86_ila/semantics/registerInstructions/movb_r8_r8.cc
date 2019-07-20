auto instr = model.NewInstr("movb_r8_r8");
UPDATE_R(R2, Concat(R2(63, 8), R1(7, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("movb_r8_r8");
