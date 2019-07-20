auto instr = model.NewInstr("salw_r16_cl");
UPDATE_R(R2, Concat(R2(63, 16), shiftLeft(62, 47)));
instr.SetUpdate(CF, 