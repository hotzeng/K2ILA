auto instr = model.NewInstr("mulxq_r64_r64_r64");
UPDATE_R(R3, mul(63, 0));
UPDATE_R(R2, mul(-1, -64));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("mulxq_r64_r64_r64");
