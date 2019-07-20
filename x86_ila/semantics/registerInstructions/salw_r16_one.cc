auto instr = model.NewInstr("salw_r16_one");
UPDATE_R(R2, Concat(R2(63, 16), shiftLeft(62, 47)));
instr.SetUpdate(CF, shiftLeft(63, 63));
instr.SetUpdate(PF, Ite( ~ (((((((((shiftLeft(47, 47)) == (BvConst(1, 1))) ^ ((shiftLeft(48, 48)) == (BvConst(1, 1)))) ^ ((shiftLeft(49, 49)) == (BvConst(1, 1)))) ^ ((shiftLeft(50, 50)) == (BvConst(1, 1)))) ^ ((shiftLeft(51, 51)) == (BvConst(1, 1)))) ^ ((shiftLeft(52, 52)) == (BvConst(1, 1)))) ^ ((shiftLeft(53, 53)) == (BvConst(1, 1)))) ^ ((shiftLeft(54, 54)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (shiftLeft(62, 47)) == (BvConst(0, 16)), bv(1), bv(0)));
instr.SetUpdate(SF, shiftLeft(62, 62));
instr.SetUpdate(OF, Ite( ((shiftLeft(63, 63)) == (BvConst(1, 1))) ^ ((shiftLeft(62, 62)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("salw_r16_one");
