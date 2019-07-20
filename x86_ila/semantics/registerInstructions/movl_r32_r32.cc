auto instr = model.NewInstr("movl_r32_r32");
UPDATE_R(R2, Concat(bv(0), R1(31, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("movl_r32_r32");
