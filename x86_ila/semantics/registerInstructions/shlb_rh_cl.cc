auto instr = model.NewInstr("shlb_rh_cl");
UPDATE_R(R2, Concat(Concat(R2(63, 16), shiftLeft(62, 55)), R2(7, 0)));
instr.SetUpdate(CF, 