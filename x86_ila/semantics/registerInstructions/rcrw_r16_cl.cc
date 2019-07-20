auto instr = model.NewInstr("rcrw_r16_cl");
UPDATE_R(R2, Concat(R2(63, 16), ror(62, 47)));
instr.SetUpdate(CF, ror(63, 63));
instr.SetUpdate(OF, 