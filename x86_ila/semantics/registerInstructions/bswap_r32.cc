auto instr = model.NewInstr("bswap_r32");
UPDATE_R(R1, Concat(Concat(Concat(bv(0), R1(7, 0)), R1(15, 8)), Concat(R1(23, 16), R1(31, 24))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("bswap_r32");
