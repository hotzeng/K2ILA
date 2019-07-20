auto instr = model.NewInstr("sarb_r8_cl");
UPDATE_R(R2, Concat(R2(63, 8), aShiftRight(63, 56)));
instr.SetUpdate(CF, 