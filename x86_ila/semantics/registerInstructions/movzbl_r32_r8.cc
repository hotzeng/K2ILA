auto instr = model.NewInstr("movzbl_r32_r8");
UPDATE_R(R2, Concat(bv(0), R1(7, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("movzbl_r32_r8");
