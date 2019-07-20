auto instr = model.NewInstr("sarb_r8_one");
UPDATE_R(R2, Concat(R2(63, 8), aShiftRight(63, 56)));
instr.SetUpdate(CF, aShiftRight(55, 55));
instr.SetUpdate(PF, Ite( ~ (((((((((aShiftRight(56, 56)) == (BvConst(1, 1))) ^ ((aShiftRight(57, 57)) == (BvConst(1, 1)))) ^ ((aShiftRight(58, 58)) == (BvConst(1, 1)))) ^ ((aShiftRight(59, 59)) == (BvConst(1, 1)))) ^ ((aShiftRight(60, 60)) == (BvConst(1, 1)))) ^ ((aShiftRight(61, 61)) == (BvConst(1, 1)))) ^ ((aShiftRight(62, 62)) == (BvConst(1, 1)))) ^ ((aShiftRight(63, 63)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (aShiftRight(63, 56)) == (BvConst(0, 8)), bv(1), bv(0)));
instr.SetUpdate(SF, aShiftRight(63, 63));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("sarb_r8_one");
