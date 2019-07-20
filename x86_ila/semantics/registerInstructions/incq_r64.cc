auto instr = model.NewInstr("incq_r64");
UPDATE_R(R1, (R1) + (bv(1)));
instr.SetUpdate(PF, Ite( ~ (((((((((add(0, 0)) == (BvConst(1, 1))) ^ ((add(1, 1)) == (BvConst(1, 1)))) ^ ((add(2, 2)) == (BvConst(1, 1)))) ^ ((add(3, 3)) == (BvConst(1, 1)))) ^ ((add(4, 4)) == (BvConst(1, 1)))) ^ ((add(5, 5)) == (BvConst(1, 1)))) ^ ((add(6, 6)) == (BvConst(1, 1)))) ^ ((add(7, 7)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(AF, Ite( (R1(3, 0)) == (BvConst(15, 4)), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( ((R1) + (bv(1))) == (BvConst(0, 64)), bv(1), bv(0)));
instr.SetUpdate(SF, add(63, 63));
instr.SetUpdate(OF, 