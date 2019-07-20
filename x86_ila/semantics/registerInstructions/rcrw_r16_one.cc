auto instr = model.NewInstr("rcrw_r16_one");
UPDATE_R(R2, Concat(R2(63, 16), ror(62, 47)));
instr.SetUpdate(CF, ror(63, 63));
instr.SetUpdate(OF, Ite( ((ror(62, 62)) == (BvConst(1, 1))) ^ ((ror(61, 61)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("rcrw_r16_one");
