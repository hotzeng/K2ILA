auto instr = model.NewInstr("sall_r32_cl");
UPDATE_R(R2, Concat(bv(0), shiftLeft(62, 31)));
instr.SetUpdate(CF, 