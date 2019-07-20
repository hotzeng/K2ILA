auto instr = model.NewInstr("sarw_r16_cl");
UPDATE_R(R2, Concat(R2(63, 16), aShiftRight(63, 48)));
instr.SetUpdate(CF, 