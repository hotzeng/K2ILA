auto instr = model.NewInstr("shrb_rh_cl");
UPDATE_R(R2, Concat(Concat(R2(63, 16), lshr(63, 56)), R2(7, 0)));
instr.SetUpdate(CF, 