auto instr = model.NewInstr("movzbw_r16_r8");
UPDATE_R(R2, Concat(R2(63, 16), Concat(bv(0), R1(7, 0))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("movzbw_r16_r8");
