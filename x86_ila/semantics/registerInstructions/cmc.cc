auto instr = model.NewInstr("cmc");
instr.SetUpdate(CF, Ite( (CF) == (BvConst(1, 1)), bv(0), bv(1)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cmc");
