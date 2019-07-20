auto instr = model.NewInstr("sarb_rh_cl");
UPDATE_R(R2, Concat(Concat(R2(63, 16), aShiftRight(63, 56)), R2(7, 0)));
instr.SetUpdate(CF, 