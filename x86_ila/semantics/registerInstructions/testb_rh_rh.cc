auto instr = model.NewInstr("testb_rh_rh");
instr.SetUpdate(CF, bv(0));
instr.SetUpdate(PF, Ite( ~ ((((((((((R2(8, 8)) & (R1(8, 8))) == (BvConst(1, 1))) ^ (((R2(9, 9)) & (R1(9, 9))) == (BvConst(1, 1)))) ^ (((R2(10, 10)) & (R1(10, 10))) == (BvConst(1, 1)))) ^ (((R2(11, 11)) & (R1(11, 11))) == (BvConst(1, 1)))) ^ (((R2(12, 12)) & (R1(12, 12))) == (BvConst(1, 1)))) ^ (((R2(13, 13)) & (R1(13, 13))) == (BvConst(1, 1)))) ^ (((R2(14, 14)) & (R1(14, 14))) == (BvConst(1, 1)))) ^ (((R2(15, 15)) & (R1(15, 15))) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( ((R2(15, 8)) & (R1(15, 8))) == (BvConst(0, 8)), bv(1), bv(0)));
instr.SetUpdate(SF, (R2(15, 15)) & (R1(15, 15)));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("testb_rh_rh");
