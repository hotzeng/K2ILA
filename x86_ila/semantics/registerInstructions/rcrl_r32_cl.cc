auto instr = model.NewInstr("rcrl_r32_cl");
UPDATE_R(R2, Concat(bv(0), ror(62, 31)));
instr.SetUpdate(CF, ror(63, 63));
instr.SetUpdate(OF, 