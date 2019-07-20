auto instr = model.NewInstr("shrb_r8_cl");
UPDATE_R(R2, Concat(R2(63, 8), lshr(63, 56)));
instr.SetUpdate(CF, 