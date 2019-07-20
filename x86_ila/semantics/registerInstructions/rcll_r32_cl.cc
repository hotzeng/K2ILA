auto instr = model.NewInstr("rcll_r32_cl");
UPDATE_R(R2, Concat(bv(0), None(62, 31)));
instr.SetUpdate(CF, None(63, 63));
instr.SetUpdate(OF, 