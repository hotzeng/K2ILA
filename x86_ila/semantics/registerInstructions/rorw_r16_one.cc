auto instr = model.NewInstr("rorw_r16_one");
UPDATE_R(R2, Concat(R2(63, 16), RRotate(R2(15, 0), 1)));
instr.SetUpdate(CF, ror(63, 63));
instr.SetUpdate(OF, Ite( ((ror(63, 63)) == (BvConst(1, 1))) ^ ((ror(62, 62)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("rorw_r16_one");
