auto instr = model.NewInstr("divw_r16");
UPDATE_R(RAX, Concat(rax(63, 16), (Concat(rdx(15, 0), rax(15, 0))) / (R1(15, 0))));
UPDATE_R(RDX, Concat(rdx(63, 16), URem(Concat(rdx(15, 0), rax(15, 0)), R1(15, 0))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("divw_r16");
