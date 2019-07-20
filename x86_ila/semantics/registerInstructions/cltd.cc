auto instr = model.NewInstr("cltd");
UPDATE_R(RDX, Concat(bv(0), None(63, 32)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("cltd");
