auto instr = model.NewInstr("bswap_r64");
UPDATE_R(R1, Concat(Concat(Concat(R1(7, 0), R1(15, 8)), Concat(R1(23, 16), R1(31, 24))), Concat(Concat(R1(39, 32), R1(47, 40)), Concat(R1(55, 48), R1(63, 56)))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("bswap_r64");
