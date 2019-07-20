auto instr = model.NewInstr("xchgb_r8_r8");
UPDATE_R(R1, Concat(R1(63, 8), R2(7, 0)));
UPDATE_R(R2, Concat(R2(63, 8), R1(7, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("xchgb_r8_r8");
