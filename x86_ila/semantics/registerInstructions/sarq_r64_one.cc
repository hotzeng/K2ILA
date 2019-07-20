auto instr = model.NewInstr("sarq_r64_one");
UPDATE_R(R2, aShiftRight(63, 0));
instr.SetUpdate(CF, aShiftRight(-1, -1));
instr.SetUpdate(PF, Ite( ~ (((((((((aShiftRight(0, 0)) == (BvConst(1, 1))) ^ ((aShiftRight(1, 1)) == (BvConst(1, 1)))) ^ ((aShiftRight(2, 2)) == (BvConst(1, 1)))) ^ ((aShiftRight(3, 3)) == (BvConst(1, 1)))) ^ ((aShiftRight(4, 4)) == (BvConst(1, 1)))) ^ ((aShiftRight(5, 5)) == (BvConst(1, 1)))) ^ ((aShiftRight(6, 6)) == (BvConst(1, 1)))) ^ ((aShiftRight(7, 7)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (aShiftRight(63, 0)) == (BvConst(0, 64)), bv(1), bv(0)));
instr.SetUpdate(SF, aShiftRight(63, 63));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("sarq_r64_one");
