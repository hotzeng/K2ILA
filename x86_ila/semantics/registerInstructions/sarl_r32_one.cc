auto instr = model.NewInstr("sarl_r32_one");
UPDATE_R(R2, Concat(bv(0), aShiftRight(63, 32)));
instr.SetUpdate(CF, aShiftRight(31, 31));
instr.SetUpdate(PF, Ite( ~ (((((((((aShiftRight(32, 32)) == (BvConst(1, 1))) ^ ((aShiftRight(33, 33)) == (BvConst(1, 1)))) ^ ((aShiftRight(34, 34)) == (BvConst(1, 1)))) ^ ((aShiftRight(35, 35)) == (BvConst(1, 1)))) ^ ((aShiftRight(36, 36)) == (BvConst(1, 1)))) ^ ((aShiftRight(37, 37)) == (BvConst(1, 1)))) ^ ((aShiftRight(38, 38)) == (BvConst(1, 1)))) ^ ((aShiftRight(39, 39)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (aShiftRight(63, 32)) == (BvConst(0, 32)), bv(1), bv(0)));
instr.SetUpdate(SF, aShiftRight(63, 63));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("sarl_r32_one");
