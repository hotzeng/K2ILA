auto instr = model.NewInstr("xchgl_eax_r32");
UPDATE_R(RAX, Concat(bv(0), R1(31, 0)));
UPDATE_R(R1, Concat(bv(0), rax(31, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("xchgl_eax_r32");
