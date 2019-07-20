auto instr = model.NewInstr("xchgw_ax_r16");
UPDATE_R(RAX, Concat(rax(63, 16), R1(15, 0)));
UPDATE_R(R1, Concat(R1(63, 16), rax(15, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("xchgw_ax_r16");
