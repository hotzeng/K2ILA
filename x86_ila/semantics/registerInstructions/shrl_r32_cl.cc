auto instr = model.NewInstr("shrl_r32_cl");
UPDATE_R(R2, Concat(bv(0), lshr(63, 32)));
instr.SetUpdate(CF, 