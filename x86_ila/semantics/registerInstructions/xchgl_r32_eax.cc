auto instr = model.NewInstr("xchgl_r32_eax");
UPDATE_R(RAX, Concat(bv(0), R2(31, 0)));
UPDATE_R(R2, Concat(bv(0), rax(31, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("xchgl_r32_eax");
