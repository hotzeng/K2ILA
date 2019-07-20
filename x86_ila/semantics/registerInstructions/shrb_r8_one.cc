auto instr = model.NewInstr("shrb_r8_one");
UPDATE_R(R2, Concat(R2(63, 8), lshr(63, 56)));
instr.SetUpdate(CF, lshr(55, 55));
instr.SetUpdate(PF, Ite( ~ (((((((((lshr(56, 56)) == (BvConst(1, 1))) ^ ((lshr(57, 57)) == (BvConst(1, 1)))) ^ ((lshr(58, 58)) == (BvConst(1, 1)))) ^ ((lshr(59, 59)) == (BvConst(1, 1)))) ^ ((lshr(60, 60)) == (BvConst(1, 1)))) ^ ((lshr(61, 61)) == (BvConst(1, 1)))) ^ ((lshr(62, 62)) == (BvConst(1, 1)))) ^ ((lshr(63, 63)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (lshr(63, 56)) == (BvConst(0, 8)), bv(1), bv(0)));
instr.SetUpdate(SF, lshr(63, 63));
instr.SetUpdate(OF, R2(7, 7));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("shrb_r8_one");
