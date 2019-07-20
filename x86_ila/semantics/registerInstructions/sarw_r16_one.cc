auto instr = model.NewInstr("sarw_r16_one");
UPDATE_R(R2, Concat(R2(63, 16), aShiftRight(63, 48)));
instr.SetUpdate(CF, aShiftRight(47, 47));
instr.SetUpdate(PF, Ite( ~ (((((((((aShiftRight(48, 48)) == (BvConst(1, 1))) ^ ((aShiftRight(49, 49)) == (BvConst(1, 1)))) ^ ((aShiftRight(50, 50)) == (BvConst(1, 1)))) ^ ((aShiftRight(51, 51)) == (BvConst(1, 1)))) ^ ((aShiftRight(52, 52)) == (BvConst(1, 1)))) ^ ((aShiftRight(53, 53)) == (BvConst(1, 1)))) ^ ((aShiftRight(54, 54)) == (BvConst(1, 1)))) ^ ((aShiftRight(55, 55)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (aShiftRight(63, 48)) == (BvConst(0, 16)), bv(1), bv(0)));
instr.SetUpdate(SF, aShiftRight(63, 63));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("sarw_r16_one");
