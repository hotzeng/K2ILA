auto instr = model.NewInstr("incl_r32");
UPDATE_R(R1, Concat(bv(0), (R1(31, 0)) + (bv(1))));
instr.SetUpdate(PF, Ite( ~ (((((((((add(32, 32)) == (BvConst(1, 1))) ^ ((add(33, 33)) == (BvConst(1, 1)))) ^ ((add(34, 34)) == (BvConst(1, 1)))) ^ ((add(35, 35)) == (BvConst(1, 1)))) ^ ((add(36, 36)) == (BvConst(1, 1)))) ^ ((add(37, 37)) == (BvConst(1, 1)))) ^ ((add(38, 38)) == (BvConst(1, 1)))) ^ ((add(39, 39)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(AF, Ite( (R1(3, 0)) == (BvConst(15, 4)), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( ((R1(31, 0)) + (bv(1))) == (BvConst(0, 32)), bv(1), bv(0)));
instr.SetUpdate(SF, add(63, 63));
instr.SetUpdate(OF, 