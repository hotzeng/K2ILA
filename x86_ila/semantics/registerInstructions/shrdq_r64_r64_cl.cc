auto instr = model.NewInstr("shrdq_r64_r64_cl");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("shrdq_r64_r64_cl");
