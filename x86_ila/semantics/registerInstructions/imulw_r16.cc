auto instr = model.NewInstr("imulw_r16");
UPDATE_R(RAX, Concat(rax(63, 16), mul(47, 32)));
UPDATE_R(RDX, Concat(rdx(63, 16), mul(63, 48)));
instr.SetUpdate(CF, 