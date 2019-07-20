auto instr = model.NewInstr("imull_r32");
UPDATE_R(RAX, Concat(bv(0), mul(31, 0)));
UPDATE_R(RDX, Concat(bv(0), mul(63, 32)));
instr.SetUpdate(CF, 