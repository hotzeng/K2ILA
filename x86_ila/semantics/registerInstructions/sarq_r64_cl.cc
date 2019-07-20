auto instr = model.NewInstr("sarq_r64_cl");
UPDATE_R(R2, aShiftRight(63, 0));
instr.SetUpdate(CF, 