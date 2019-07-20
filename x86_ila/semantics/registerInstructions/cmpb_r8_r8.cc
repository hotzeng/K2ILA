auto instr = model.NewInstr("cmpb_r8_r8");
instr.SetUpdate(CF, Ite( ~ ((add(63, 63)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(PF, Ite( ~ (((((((((add(55, 55)) == (BvConst(1, 1))) ^ ((add(56, 56)) == (BvConst(1, 1)))) ^ ((add(57, 57)) == (BvConst(1, 1)))) ^ ((add(58, 58)) == (BvConst(1, 1)))) ^ ((add(59, 59)) == (BvConst(1, 1)))) ^ ((add(60, 60)) == (BvConst(1, 1)))) ^ ((add(61, 61)) == (BvConst(1, 1)))) ^ ((add(62, 62)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(AF, ((R1(4, 4)) ^ (R2(4, 4))) ^ (add(59, 59)));
instr.SetUpdate(ZF, Ite( (add(62, 55)) == (BvConst(0, 8)), bv(1), bv(0)));
instr.SetUpdate(SF, add(62, 62));
instr.SetUpdate(OF, Ite( ((~ (R1(7, 7))) == (BvConst(1, 1))) == ((R2(7, 7)) == ((bv(1)) == ((add(62, 62)) == (BvConst(1, 1))))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmpb_r8_r8");
