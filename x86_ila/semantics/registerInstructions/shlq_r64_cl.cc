auto instr = model.NewInstr("shlq_r64_cl");
UPDATE_R(R2, shiftLeft(62, -1));
instr.SetUpdate(CF, 