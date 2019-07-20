auto instr = model.NewInstr("rcll_r32_one");
UPDATE_R(R2, Concat(bv(0), None(62, 31)));
instr.SetUpdate(CF, None(63, 63));
instr.SetUpdate(OF, Ite( ((None(63, 63)) == (BvConst(1, 1))) ^ ((None(62, 62)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("rcll_r32_one");
