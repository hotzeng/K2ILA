auto instr = model.NewInstr("shrq_r64_one");
UPDATE_R(R2, lshr(63, 0));
instr.SetUpdate(CF, lshr(-1, -1));
instr.SetUpdate(PF, Ite( ~ (((((((((lshr(0, 0)) == (BvConst(1, 1))) ^ ((lshr(1, 1)) == (BvConst(1, 1)))) ^ ((lshr(2, 2)) == (BvConst(1, 1)))) ^ ((lshr(3, 3)) == (BvConst(1, 1)))) ^ ((lshr(4, 4)) == (BvConst(1, 1)))) ^ ((lshr(5, 5)) == (BvConst(1, 1)))) ^ ((lshr(6, 6)) == (BvConst(1, 1)))) ^ ((lshr(7, 7)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (lshr(63, 0)) == (BvConst(0, 64)), bv(1), bv(0)));
instr.SetUpdate(SF, lshr(63, 63));
instr.SetUpdate(OF, R2(63, 63));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("shrq_r64_one");
