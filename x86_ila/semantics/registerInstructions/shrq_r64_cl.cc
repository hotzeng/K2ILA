auto instr = model.NewInstr("shrq_r64_cl");
UPDATE_R(R2, lshr(63, 0));
instr.SetUpdate(CF, 