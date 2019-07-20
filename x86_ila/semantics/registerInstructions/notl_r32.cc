auto instr = model.NewInstr("notl_r32");
UPDATE_R(R1, Concat(bv(0), ~ (R1(31, 0))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("notl_r32");
