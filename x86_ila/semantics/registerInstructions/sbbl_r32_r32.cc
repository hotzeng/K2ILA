auto instr = model.NewInstr("sbbl_r32_r32");
UPDATE_R(R2, Concat(bv(0), add(62, 31)));
instr.SetUpdate(CF, Ite( ~ ((add(63, 63)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(PF, Ite( ~ (((((((((add(31, 31)) == (BvConst(1, 1))) ^ ((add(32, 32)) == (BvConst(1, 1)))) ^ ((add(33, 33)) == (BvConst(1, 1)))) ^ ((add(34, 34)) == (BvConst(1, 1)))) ^ ((add(35, 35)) == (BvConst(1, 1)))) ^ ((add(36, 36)) == (BvConst(1, 1)))) ^ ((add(37, 37)) == (BvConst(1, 1)))) ^ ((add(38, 38)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(AF, ((R1(4, 4)) ^ (R2(4, 4))) ^ (add(35, 35)));
instr.SetUpdate(ZF, Ite( (add(62, 31)) == (BvConst(0, 32)), bv(1), bv(0)));
instr.SetUpdate(SF, add(62, 62));
instr.SetUpdate(OF, Ite( ((~ (R1(31, 31))) == (BvConst(1, 1))) == ((R2(31, 31)) == ((bv(1)) == ((add(62, 62)) == (BvConst(1, 1))))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("sbbl_r32_r32");
