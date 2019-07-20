auto instr = model.NewInstr("shlq_r64_one");
UPDATE_R(R2, shiftLeft(62, -1));
instr.SetUpdate(CF, shiftLeft(63, 63));
instr.SetUpdate(PF, Ite( ~ (((((((((shiftLeft(-1, -1)) == (BvConst(1, 1))) ^ ((shiftLeft(0, 0)) == (BvConst(1, 1)))) ^ ((shiftLeft(1, 1)) == (BvConst(1, 1)))) ^ ((shiftLeft(2, 2)) == (BvConst(1, 1)))) ^ ((shiftLeft(3, 3)) == (BvConst(1, 1)))) ^ ((shiftLeft(4, 4)) == (BvConst(1, 1)))) ^ ((shiftLeft(5, 5)) == (BvConst(1, 1)))) ^ ((shiftLeft(6, 6)) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (shiftLeft(62, -1)) == (BvConst(0, 64)), bv(1), bv(0)));
instr.SetUpdate(SF, shiftLeft(62, 62));
instr.SetUpdate(OF, Ite( ((shiftLeft(63, 63)) == (BvConst(1, 1))) ^ ((shiftLeft(62, 62)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("shlq_r64_one");
