auto instr = model.NewInstr("blsiq_r64_r64");
UPDATE_R(R2, ((bv(1)) + (~ (R1))) & (R1));
instr.SetUpdate(CF, Ite( ~ ((R1) == (BvConst(0, 64))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( (((bv(1)) + (~ (R1))) & (R1)) == (BvConst(0, 64)), bv(1), bv(0)));
instr.SetUpdate(SF, (add(63, 63)) & (R1(63, 63)));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("blsiq_r64_r64");
