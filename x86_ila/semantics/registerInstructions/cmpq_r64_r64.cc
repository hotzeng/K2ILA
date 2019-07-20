auto instr = model.NewInstr("cmpq_r64_r64");
instr.SetUpdate(CF, Ite( ~ ((add(63, 63)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(PF, Ite( ~ (((((((((add(-1, -1)) == (BvConst(1, 1))) ^ ((add(0, 0)) == (BvConst(1, 1)))) ^ ((add(1, 1)) == (BvConst(1, 1)))) ^ ((add(2, 2)) == (BvConst(1, 1)))) ^ ((add(3, 3)) == (BvConst(1, 1)))) ^ ((add(4, 4)) == (BvConst(1, 1)))) ^ ((add(5, 5)) == (BvConst(1, 1)))) ^ ((add(6, 6)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(AF, ((R1(4, 4)) ^ (R2(4, 4))) ^ (add(3, 3)));
instr.SetUpdate(ZF, Ite( (add(62, -1)) == (BvConst(0, 64)), bv(1), bv(0)));
instr.SetUpdate(SF, add(62, 62));
instr.SetUpdate(OF, Ite( ((~ (R1(63, 63))) == (BvConst(1, 1))) == ((R2(63, 63)) == ((bv(1)) == ((add(62, 62)) == (BvConst(1, 1))))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmpq_r64_r64");
