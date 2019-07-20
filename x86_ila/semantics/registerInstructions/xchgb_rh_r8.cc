auto instr = model.NewInstr("xchgb_rh_r8");
UPDATE_R(R2, Concat(Concat(R2(63, 16), R1(7, 0)), R2(7, 0)));
UPDATE_R(R1, Concat(R1(63, 8), R2(15, 8)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("xchgb_rh_r8");
