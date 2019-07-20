auto instr = model.NewInstr("divb_rh");
UPDATE_R(RAX, Concat(Concat(rax(63, 16), URem(rax(15, 0), R1(15, 8))), (rax(15, 0)) / (R1(15, 8))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("divb_rh");
