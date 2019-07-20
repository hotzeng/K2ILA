auto instr = model.NewInstr("shldw_r16_r16_cl");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("shldw_r16_r16_cl");
