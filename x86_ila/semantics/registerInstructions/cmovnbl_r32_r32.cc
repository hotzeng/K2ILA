auto instr = model.NewInstr("cmovnbl_r32_r32");
UPDATE_R(R2, Concat(bv(0), Ite(~ ((CF) == (BvConst(1, 1))), R1(31, 0), R2(31, 0))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmovnbl_r32_r32");
