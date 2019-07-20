auto instr = model.NewInstr("notw_r16");
UPDATE_R(R1, Concat(R1(63, 16), ~ (R1(15, 0))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("notw_r16");
