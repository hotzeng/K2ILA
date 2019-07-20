auto instr = model.NewInstr("imulw_r16_r16");
UPDATE_R(R2, Concat(R2(63, 16), mul(47, 32)));
instr.SetUpdate(CF, 