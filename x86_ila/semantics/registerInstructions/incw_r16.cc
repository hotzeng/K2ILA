auto instr = model.NewInstr("incw_r16");
UPDATE_R(R1, Concat(R1(63, 16), (R1(15, 0)) + (bv(1))));
instr.SetUpdate(PF, Ite( ~ (((((((((add(48, 48)) == (BvConst(1, 1))) ^ ((add(49, 49)) == (BvConst(1, 1)))) ^ ((add(50, 50)) == (BvConst(1, 1)))) ^ ((add(51, 51)) == (BvConst(1, 1)))) ^ ((add(52, 52)) == (BvConst(1, 1)))) ^ ((add(53, 53)) == (BvConst(1, 1)))) ^ ((add(54, 54)) == (BvConst(1, 1)))) ^ ((add(55, 55)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(AF, Ite( (R1(3, 0)) == (BvConst(15, 4)), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( ((R1(15, 0)) + (bv(1))) == (BvConst(0, 16)), bv(1), bv(0)));
instr.SetUpdate(SF, add(63, 63));
instr.SetUpdate(OF, 