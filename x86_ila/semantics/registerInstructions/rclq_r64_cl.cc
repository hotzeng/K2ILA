auto instr = model.NewInstr("rclq_r64_cl");
UPDATE_R(R2, None(62, -1));
instr.SetUpdate(CF, None(63, 63));
instr.SetUpdate(OF, 