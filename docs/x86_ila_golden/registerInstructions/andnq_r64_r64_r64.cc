auto instr = model.NewInstr("andnq_r64_r64_r64");
UPDATE_R(R3, ~R2 & R1);
instr.SetUpdate(CF, bv(0));
instr.SetUpdate(ZF, Ite( ~R2 & R1 == BvConst(0, 64), bv(1), bv(0)));
instr.SetUpdate(SF, ~R2(63, 63) & R1(63, 63));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("andnq_r64_r64_r64");
