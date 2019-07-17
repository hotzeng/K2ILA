auto instr = model.NewInstr("mulb_rh");
UPDATE_R(RAX, Concat(rax(63, 16), (Concat(bv(0), R1(15, 8))) * (Concat(bv(0), rax(7, 0)))));
instr.SetUpdate(CF, Ite( ~ ((mul(63, 56)) == (BvConst(0, 8))), bv(1), bv(0)));
instr.SetUpdate(OF, Ite( ~ ((mul(63, 56)) == (BvConst(0, 8))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("mulb_rh");
