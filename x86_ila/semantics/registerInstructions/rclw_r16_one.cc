auto instr = model.NewInstr("rclw_r16_one");
UPDATE_R(R2, Concat(R2(63, 16), None(62, 47)));
instr.SetUpdate(CF, None(63, 63));
instr.SetUpdate(OF, Ite( ((None(63, 63)) == (BvConst(1, 1))) ^ ((None(62, 62)) == (BvConst(1, 1))), bv(1), bv(0)));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("rclw_r16_one");
