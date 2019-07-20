auto instr = model.NewInstr("rcrb_rh_cl");
UPDATE_R(R2, Concat(Concat(R2(63, 16), ror(62, 55)), R2(7, 0)));
instr.SetUpdate(CF, ror(63, 63));
instr.SetUpdate(OF, 