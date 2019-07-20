auto instr = model.NewInstr("rcrb_rh_one");
UPDATE_R(R2, Concat(Concat(R2(63, 16), ror(62, 55)), R2(7, 0)));
instr.SetUpdate(CF, ror(63, 63));
instr.SetUpdate(OF, Ite( ((ror(62, 62)) == (BvConst(1, 1))) ^ ((ror(61, 61)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("rcrb_rh_one");
