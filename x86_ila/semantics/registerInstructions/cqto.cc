auto instr = model.NewInstr("cqto");
UPDATE_R(RDX, None(63, 0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cqto");
