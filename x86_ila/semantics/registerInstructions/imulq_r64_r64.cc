auto instr = model.NewInstr("imulq_r64_r64");
UPDATE_R(R2, mul(-1, -64));
instr.SetUpdate(CF, 