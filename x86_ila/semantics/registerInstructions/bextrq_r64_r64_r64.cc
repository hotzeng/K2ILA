auto instr = model.NewInstr("bextrq_r64_r64_r64");
UPDATE_R(R3, (lshr(-385, -448)) & (~ (shiftLeft(-385, -448))));
instr.SetUpdate(CF, bv(0));
instr.SetUpdate(ZF, Ite( ((lshr(-385, -448)) & (~ (shiftLeft(-385, -448)))) == (BvConst(0, 64)), bv(1), bv(0)));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("bextrq_r64_r64_r64");
