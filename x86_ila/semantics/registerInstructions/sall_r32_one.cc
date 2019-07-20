auto instr = model.NewInstr("sall_r32_one");
UPDATE_R(R2, Concat(bv(0), shiftLeft(62, 31)));
instr.SetUpdate(CF, shiftLeft(63, 63));
instr.SetUpdate(PF, Ite( ~ (((((((((shiftLeft(31, 31)) == (BvConst(1, 1))) ^ ((shiftLeft(32, 32)) == (BvConst(1, 1)))) ^ ((shiftLeft(33, 33)) == (BvConst(1, 1)))) ^ ((shiftLeft(34, 34)) == (BvConst(1, 1)))) ^ ((shiftLeft(35, 35)) == (BvConst(1, 1)))) ^ ((shiftLeft(36, 36)) == (BvConst(1, 1)))) ^ ((shiftLeft(37, 37)) == (BvConst(1, 1)))) ^ ((shiftLeft(38, 38)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (shiftLeft(62, 31)) == (BvConst(0, 32)), bv(1), bv(0)));
instr.SetUpdate(SF, shiftLeft(62, 62));
instr.SetUpdate(OF, Ite( ((shiftLeft(63, 63)) == (BvConst(1, 1))) ^ ((shiftLeft(62, 62)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("sall_r32_one");
