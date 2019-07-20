auto instr = model.NewInstr("shrw_r16_cl");
UPDATE_R(R2, Concat(R2(63, 16), lshr(63, 48)));
instr.SetUpdate(CF, 