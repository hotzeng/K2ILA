auto instr = model.NewInstr("imull_r32_r32");
UPDATE_R(R2, Concat(bv(0), mul(31, 0)));
instr.SetUpdate(CF, 