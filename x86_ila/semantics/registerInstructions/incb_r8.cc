auto instr = model.NewInstr("incb_r8");
UPDATE_R(R1, Concat(R1(63, 8), (R1(7, 0)) + (bv(1))));
instr.SetUpdate(PF, Ite( ~ (((((((((add(56, 56)) == (BvConst(1, 1))) ^ ((add(57, 57)) == (BvConst(1, 1)))) ^ ((add(58, 58)) == (BvConst(1, 1)))) ^ ((add(59, 59)) == (BvConst(1, 1)))) ^ ((add(60, 60)) == (BvConst(1, 1)))) ^ ((add(61, 61)) == (BvConst(1, 1)))) ^ ((add(62, 62)) == (BvConst(1, 1)))) ^ ((add(63, 63)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(AF, Ite( (R1(3, 0)) == (BvConst(15, 4)), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( ((R1(7, 0)) + (bv(1))) == (BvConst(0, 8)), bv(1), bv(0)));
instr.SetUpdate(SF, add(63, 63));
instr.SetUpdate(OF, 