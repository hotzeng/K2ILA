auto instr = model.NewInstr("shrxq_r64_r64_r64");
UPDATE_R(R3, lshr(63, 0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("shrxq_r64_r64_r64");
