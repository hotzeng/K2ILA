auto instr = model.NewInstr("mulxl_r32_r32_r32");
UPDATE_R(R3, Concat(bv(0), mul(63, 32)));
UPDATE_R(R2, Concat(bv(0), mul(31, 0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("mulxl_r32_r32_r32");
