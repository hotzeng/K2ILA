auto instr = model.NewInstr("shrw_r16_one");
UPDATE_R(R2, Concat(R2(63, 16), lshr(63, 48)));
instr.SetUpdate(CF, lshr(47, 47));
instr.SetUpdate(PF, Ite( ~ (((((((((lshr(48, 48)) == (BvConst(1, 1))) ^ ((lshr(49, 49)) == (BvConst(1, 1)))) ^ ((lshr(50, 50)) == (BvConst(1, 1)))) ^ ((lshr(51, 51)) == (BvConst(1, 1)))) ^ ((lshr(52, 52)) == (BvConst(1, 1)))) ^ ((lshr(53, 53)) == (BvConst(1, 1)))) ^ ((lshr(54, 54)) == (BvConst(1, 1)))) ^ ((lshr(55, 55)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (lshr(63, 48)) == (BvConst(0, 16)), bv(1), bv(0)));
instr.SetUpdate(SF, lshr(63, 63));
instr.SetUpdate(OF, R2(15, 15));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("shrw_r16_one");
