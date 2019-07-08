auto instr = model.NewInstr(ANDNQ-R64-R64-R64)
instr.SetUpdate(R3, ~R2 & R1)
instr.SetUpdate(CF, bv(0, 1))
instr.SetUpdate(ZF, Ite( ~R2 & R1 == bv(0, 64), bv(1, 1), bv(0, 1)))
instr.SetUpdate(SF, ~R2(63, 63) & R1(63, 63))
instr.SetUpdate(OF, bv(0, 1))
RECORD_INST("ANDNQ-R64-R64-R64");
