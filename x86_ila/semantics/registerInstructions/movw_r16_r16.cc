auto instr = model.NewInstr("movw_r16_r16");
UPDATE_R(R2, Concat(R2(63, 16), R1(15, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("movw_r16_r16");
