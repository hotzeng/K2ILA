auto instr = model.NewInstr("rorl_r32_one");
UPDATE_R(R2, Concat(bv(0), RRotate(R2(31, 0), 1)));
instr.SetUpdate(CF, ror(63, 63));
instr.SetUpdate(OF, Ite( ((ror(63, 63)) == (BvConst(1, 1))) ^ ((ror(62, 62)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("rorl_r32_one");
