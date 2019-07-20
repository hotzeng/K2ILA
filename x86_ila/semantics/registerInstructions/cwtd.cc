auto instr = model.NewInstr("cwtd");
UPDATE_R(RDX, Concat(rdx(63, 16), None(63, 48)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cwtd");
