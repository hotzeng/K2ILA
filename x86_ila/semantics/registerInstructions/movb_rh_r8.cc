auto instr = model.NewInstr("movb_rh_r8");
UPDATE_R(R2, Concat(Concat(R2(63, 16), R1(7, 0)), R2(7, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("movb_rh_r8");
