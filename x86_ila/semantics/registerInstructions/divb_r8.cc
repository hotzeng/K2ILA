auto instr = model.NewInstr("divb_r8");
UPDATE_R(RAX, Concat(Concat(rax(63, 16), URem(rax(15, 0), R1(7, 0))), (rax(15, 0)) / (R1(7, 0))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("divb_r8");
