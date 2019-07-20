auto instr = model.NewInstr("rclb_rh_cl");
UPDATE_R(R2, Concat(Concat(R2(63, 16), None(62, 55)), R2(7, 0)));
instr.SetUpdate(CF, None(63, 63));
instr.SetUpdate(OF, 