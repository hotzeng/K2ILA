auto instr = model.NewInstr("cmpw_r16_r16");
instr.SetUpdate(CF, Ite( ~ ((add(63, 63)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(PF, Ite( ~ (((((((((add(47, 47)) == (BvConst(1, 1))) ^ ((add(48, 48)) == (BvConst(1, 1)))) ^ ((add(49, 49)) == (BvConst(1, 1)))) ^ ((add(50, 50)) == (BvConst(1, 1)))) ^ ((add(51, 51)) == (BvConst(1, 1)))) ^ ((add(52, 52)) == (BvConst(1, 1)))) ^ ((add(53, 53)) == (BvConst(1, 1)))) ^ ((add(54, 54)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(AF, ((R1(4, 4)) ^ (R2(4, 4))) ^ (add(51, 51)));
instr.SetUpdate(ZF, Ite( (add(62, 47)) == (BvConst(0, 16)), bv(1), bv(0)));
instr.SetUpdate(SF, add(62, 62));
instr.SetUpdate(OF, Ite( ((~ (R1(15, 15))) == (BvConst(1, 1))) == ((R2(15, 15)) == ((bv(1)) == ((add(62, 62)) == (BvConst(1, 1))))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmpw_r16_r16");
