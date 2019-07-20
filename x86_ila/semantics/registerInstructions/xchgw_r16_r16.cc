auto instr = model.NewInstr("xchgw_r16_r16");
UPDATE_R(R1, Concat(R1(63, 16), R2(15, 0)));
UPDATE_R(R2, Concat(R2(63, 16), R1(15, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("xchgw_r16_r16");
