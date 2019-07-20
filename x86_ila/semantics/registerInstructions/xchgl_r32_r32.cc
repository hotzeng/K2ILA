auto instr = model.NewInstr("xchgl_r32_r32");
UPDATE_R(R1, Concat(bv(0), R2(31, 0)));
UPDATE_R(R2, Concat(bv(0), R1(31, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("xchgl_r32_r32");
