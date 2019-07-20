auto instr = model.NewInstr("notb_rh");
UPDATE_R(R1, Concat(Concat(R1(63, 16), ~ (R1(15, 8))), R1(7, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("notb_rh");
