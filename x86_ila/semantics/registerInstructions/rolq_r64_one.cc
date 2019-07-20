auto instr = model.NewInstr("rolq_r64_one");
instr.SetUpdate(CF, None(0, 0));
instr.SetUpdate(OF, Ite( ((None(63, 63)) == (BvConst(1, 1))) ^ ((None(0, 0)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("rolq_r64_one");
