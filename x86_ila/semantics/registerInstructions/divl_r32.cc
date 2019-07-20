auto instr = model.NewInstr("divl_r32");
UPDATE_R(RAX, Concat(bv(0), (Concat(rdx(31, 0), rax(31, 0))) / (R1(31, 0))));
UPDATE_R(RDX, Concat(bv(0), URem(Concat(rdx(31, 0), rax(31, 0)), R1(31, 0))));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("divl_r32");
