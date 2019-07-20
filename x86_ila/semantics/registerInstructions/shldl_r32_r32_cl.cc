auto instr = model.NewInstr("shldl_r32_r32_cl");
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("shldl_r32_r32_cl");
