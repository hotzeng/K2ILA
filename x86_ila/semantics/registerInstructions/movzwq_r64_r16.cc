auto instr = model.NewInstr("movzwq_r64_r16");
UPDATE_R(R2, Concat(bv(0), R1(15, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("movzwq_r64_r16");
