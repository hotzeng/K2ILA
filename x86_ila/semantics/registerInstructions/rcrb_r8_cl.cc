auto instr = model.NewInstr("rcrb_r8_cl");
UPDATE_R(R2, Concat(R2(63, 8), ror(62, 55)));
instr.SetUpdate(CF, ror(63, 63));
instr.SetUpdate(OF, 