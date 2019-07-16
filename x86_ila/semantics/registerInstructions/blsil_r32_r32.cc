auto instr = model.NewInstr("blsil_r32_r32");
UPDATE_R(R2, Concat(bv(0), ((bv(1)) + (~ (R1(31, 0)))) & (R1(31, 0))));
instr.SetUpdate(CF, Ite( ~ ((R1(31, 0)) == (BvConst(0, 32))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (((bv(1)) + (~ (R1(31, 0)))) & (R1(31, 0))) == (BvConst(0, 32)), bv(1), bv(0)));
instr.SetUpdate(SF, (add(63, 63)) & (R1(31, 31)));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("blsil_r32_r32");
