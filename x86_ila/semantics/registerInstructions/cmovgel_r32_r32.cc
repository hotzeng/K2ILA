auto instr = model.NewInstr("cmovgel_r32_r32");
UPDATE_R(R2, Concat(bv(0), Ite(((SF) == (BvConst(1, 1))) == ((OF) == (BvConst(1, 1))), R1(31, 0), R2(31, 0))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmovgel_r32_r32");
