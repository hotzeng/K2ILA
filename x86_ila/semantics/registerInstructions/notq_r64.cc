auto instr = model.NewInstr("notq_r64");
UPDATE_R(R1, ~ (R1));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("notq_r64");
