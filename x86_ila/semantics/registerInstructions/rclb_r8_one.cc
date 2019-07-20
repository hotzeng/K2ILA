auto instr = model.NewInstr("rclb_r8_one");
UPDATE_R(R2, Concat(R2(63, 8), None(62, 55)));
instr.SetUpdate(CF, None(63, 63));
instr.SetUpdate(OF, Ite( ((None(63, 63)) == (BvConst(1, 1))) ^ ((None(62, 62)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("rclb_r8_one");
