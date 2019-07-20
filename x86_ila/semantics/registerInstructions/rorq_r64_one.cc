auto instr = model.NewInstr("rorq_r64_one");
instr.SetUpdate(CF, ror(63, 63));
instr.SetUpdate(OF, Ite( ((ror(63, 63)) == (BvConst(1, 1))) ^ ((ror(62, 62)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("rorq_r64_one");
