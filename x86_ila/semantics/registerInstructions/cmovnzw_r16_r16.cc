auto instr = model.NewInstr("cmovnzw_r16_r16");
UPDATE_R(R2, Concat(R2(63, 16), Ite(~ ((ZF) == (BvConst(1, 1))), R1(15, 0), R2(15, 0))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmovnzw_r16_r16");
