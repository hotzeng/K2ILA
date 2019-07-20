auto instr = model.NewInstr("testb_rh_r8");
instr.SetUpdate(CF, bv(0));
instr.SetUpdate(PF, Ite( ~ ((((((((((R2(8, 8)) & (R1(0, 0))) == (BvConst(1, 1))) ^ (((R2(9, 9)) & (R1(1, 1))) == (BvConst(1, 1)))) ^ (((R2(10, 10)) & (R1(2, 2))) == (BvConst(1, 1)))) ^ (((R2(11, 11)) & (R1(3, 3))) == (BvConst(1, 1)))) ^ (((R2(12, 12)) & (R1(4, 4))) == (BvConst(1, 1)))) ^ (((R2(13, 13)) & (R1(5, 5))) == (BvConst(1, 1)))) ^ (((R2(14, 14)) & (R1(6, 6))) == (BvConst(1, 1)))) ^ (((R2(15, 15)) & (R1(7, 7))) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( ((R2(15, 8)) & (R1(7, 0))) == (BvConst(0, 8)), bv(1), bv(0)));
instr.SetUpdate(SF, (R2(15, 15)) & (R1(7, 7)));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("testb_rh_r8");
