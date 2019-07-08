auto instr = model.NewInstr("andnq_r64_r64_r64");
// decode to be done
// state update 
/// can pc update be generated automatically?
instr.SetUpdate(pc, nxt_pc);
UPDATE_R(R3, ~R2 + R1)
instr.SetUpdate(CF, bv(0))
instr.SetUpdate(ZF, Ite( (~R2 + R1) == BvConst(0, 64), bv(1), bv(0) ))
instr.SetUpdate(SF, bv(0))
instr.SetUpdate(OF, bv(0))

RECORD_INST("andnq_r64_r64_r64");
