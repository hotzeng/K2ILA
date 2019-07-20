auto instr = model.NewInstr("rclb_r8_cl");
UPDATE_R(R2, Concat(R2(63, 8), None(62, 55)));
instr.SetUpdate(CF, None(63, 63));
instr.SetUpdate(OF, 