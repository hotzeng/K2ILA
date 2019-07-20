auto instr = model.NewInstr("andnl_r32_r32_r32");
UPDATE_R(R3, Concat(bv(0), (~ (R2(31, 0))) & (R1(31, 0))));
instr.SetUpdate(CF, bv(0));
instr.SetUpdate(ZF, Ite( ((~ (R2(31, 0))) & (R1(31, 0))) == (BvConst(0, 32)), bv(1), bv(0)));
instr.SetUpdate(SF, (~ (R2(31, 31))) & (R1(31, 31)));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("andnl_r32_r32_r32");
