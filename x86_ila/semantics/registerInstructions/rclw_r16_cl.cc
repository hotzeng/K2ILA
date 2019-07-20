auto instr = model.NewInstr("rclw_r16_cl");
UPDATE_R(R2, Concat(R2(63, 16), None(62, 47)));
instr.SetUpdate(CF, None(63, 63));
instr.SetUpdate(OF, 