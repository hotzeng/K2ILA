auto instr = model.NewInstr("testb_r8_rh");
instr.SetUpdate(CF, bv(0));
instr.SetUpdate(PF, Ite( ~ ((((((((((R2(0, 0)) & (R1(8, 8))) == (BvConst(1, 1))) ^ (((R2(1, 1)) & (R1(9, 9))) == (BvConst(1, 1)))) ^ (((R2(2, 2)) & (R1(10, 10))) == (BvConst(1, 1)))) ^ (((R2(3, 3)) & (R1(11, 11))) == (BvConst(1, 1)))) ^ (((R2(4, 4)) & (R1(12, 12))) == (BvConst(1, 1)))) ^ (((R2(5, 5)) & (R1(13, 13))) == (BvConst(1, 1)))) ^ (((R2(6, 6)) & (R1(14, 14))) == (BvConst(1, 1)))) ^ (((R2(7, 7)) & (R1(15, 15))) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( ((R2(7, 0)) & (R1(15, 8))) == (BvConst(0, 8)), bv(1), bv(0)));
instr.SetUpdate(SF, (R2(7, 7)) & (R1(15, 15)));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("testb_r8_rh");
