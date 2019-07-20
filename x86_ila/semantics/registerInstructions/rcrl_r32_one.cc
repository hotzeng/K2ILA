auto instr = model.NewInstr("rcrl_r32_one");
UPDATE_R(R2, Concat(bv(0), ror(62, 31)));
instr.SetUpdate(CF, ror(63, 63));
instr.SetUpdate(OF, Ite( ((ror(62, 62)) == (BvConst(1, 1))) ^ ((ror(61, 61)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("rcrl_r32_one");
