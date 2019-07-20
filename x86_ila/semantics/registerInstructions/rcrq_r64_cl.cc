auto instr = model.NewInstr("rcrq_r64_cl");
UPDATE_R(R2, ror(62, -1));
instr.SetUpdate(CF, ror(63, 63));
instr.SetUpdate(OF, 