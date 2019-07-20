auto instr = model.NewInstr("salq_r64_cl");
UPDATE_R(R2, shiftLeft(62, -1));
instr.SetUpdate(CF, 