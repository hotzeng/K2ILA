auto instr = model.NewInstr("notb_r8");
UPDATE_R(R1, Concat(R1(63, 8), ~ (R1(7, 0))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("notb_r8");
