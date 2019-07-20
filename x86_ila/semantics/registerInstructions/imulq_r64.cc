auto instr = model.NewInstr("imulq_r64");
UPDATE_R(RAX, mul(-1, -64));
UPDATE_R(RDX, mul(63, 0));
instr.SetUpdate(CF, 