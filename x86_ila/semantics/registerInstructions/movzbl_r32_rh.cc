auto instr = model.NewInstr("movzbl_r32_rh");
UPDATE_R(R2, Concat(bv(0), R1(15, 8)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("movzbl_r32_rh");
