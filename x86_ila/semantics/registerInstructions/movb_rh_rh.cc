auto instr = model.NewInstr("movb_rh_rh");
UPDATE_R(R2, Concat(Concat(R2(63, 16), R1(15, 8)), R2(7, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("movb_rh_rh");
