auto instr = model.NewInstr("bextrl_r32_r32_r32");
UPDATE_R(R3, Concat(bv(0), (lshr(-417, -448)) & (~ (shiftLeft(-417, -448)))));
instr.SetUpdate(CF, bv(0));
instr.SetUpdate(ZF, Ite( ((lshr(-417, -448)) & (~ (shiftLeft(-417, -448)))) == (BvConst(0, 32)), bv(1), bv(0)));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("bextrl_r32_r32_r32");
