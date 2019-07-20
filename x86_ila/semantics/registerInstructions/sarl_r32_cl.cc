auto instr = model.NewInstr("sarl_r32_cl");
UPDATE_R(R2, Concat(bv(0), aShiftRight(63, 32)));
instr.SetUpdate(CF, 