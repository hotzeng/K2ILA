auto instr = model.NewInstr("shlb_r8_cl");
UPDATE_R(R2, Concat(R2(63, 8), shiftLeft(62, 55)));
instr.SetUpdate(CF, 