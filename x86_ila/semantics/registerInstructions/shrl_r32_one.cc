auto instr = model.NewInstr("shrl_r32_one");
UPDATE_R(R2, Concat(bv(0), lshr(63, 32)));
instr.SetUpdate(CF, lshr(31, 31));
instr.SetUpdate(PF, Ite( ~ (((((((((lshr(32, 32)) == (BvConst(1, 1))) ^ ((lshr(33, 33)) == (BvConst(1, 1)))) ^ ((lshr(34, 34)) == (BvConst(1, 1)))) ^ ((lshr(35, 35)) == (BvConst(1, 1)))) ^ ((lshr(36, 36)) == (BvConst(1, 1)))) ^ ((lshr(37, 37)) == (BvConst(1, 1)))) ^ ((lshr(38, 38)) == (BvConst(1, 1)))) ^ ((lshr(39, 39)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (lshr(63, 32)) == (BvConst(0, 32)), bv(1), bv(0)));
instr.SetUpdate(SF, lshr(63, 63));
instr.SetUpdate(OF, R2(31, 31));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("shrl_r32_one");
