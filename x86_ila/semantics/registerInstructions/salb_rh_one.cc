auto instr = model.NewInstr("salb_rh_one");
UPDATE_R(R2, Concat(Concat(R2(63, 16), shiftLeft(62, 55)), R2(7, 0)));
instr.SetUpdate(CF, shiftLeft(63, 63));
instr.SetUpdate(PF, Ite( ~ (((((((((shiftLeft(55, 55)) == (BvConst(1, 1))) ^ ((shiftLeft(56, 56)) == (BvConst(1, 1)))) ^ ((shiftLeft(57, 57)) == (BvConst(1, 1)))) ^ ((shiftLeft(58, 58)) == (BvConst(1, 1)))) ^ ((shiftLeft(59, 59)) == (BvConst(1, 1)))) ^ ((shiftLeft(60, 60)) == (BvConst(1, 1)))) ^ ((shiftLeft(61, 61)) == (BvConst(1, 1)))) ^ ((shiftLeft(62, 62)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (shiftLeft(62, 55)) == (BvConst(0, 8)), bv(1), bv(0)));
instr.SetUpdate(SF, shiftLeft(62, 62));
instr.SetUpdate(OF, Ite( ((shiftLeft(63, 63)) == (BvConst(1, 1))) ^ ((shiftLeft(62, 62)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("salb_rh_one");
