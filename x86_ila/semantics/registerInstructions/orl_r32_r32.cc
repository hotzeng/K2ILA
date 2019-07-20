auto instr = model.NewInstr("orl_r32_r32");
UPDATE_R(R2, Concat(bv(0), (R2(31, 0)) | (R1(31, 0))));
instr.SetUpdate(CF, bv(0));
instr.SetUpdate(PF, Ite( ~ ((((((((((R2(0, 0)) | (R1(0, 0))) == (BvConst(1, 1))) ^ (((R2(1, 1)) | (R1(1, 1))) == (BvConst(1, 1)))) ^ (((R2(2, 2)) | (R1(2, 2))) == (BvConst(1, 1)))) ^ (((R2(3, 3)) | (R1(3, 3))) == (BvConst(1, 1)))) ^ (((R2(4, 4)) | (R1(4, 4))) == (BvConst(1, 1)))) ^ (((R2(5, 5)) | (R1(5, 5))) == (BvConst(1, 1)))) ^ (((R2(6, 6)) | (R1(6, 6))) == (BvConst(1, 1)))) ^ (((R2(7, 7)) | (R1(7, 7))) == (BvConst(1, 1)))), bv(1), bv(0)));
instr.SetUpdate(ZF, Ite( ((R2(31, 0)) | (R1(31, 0))) == (BvConst(0, 32)), bv(1), bv(0)));
instr.SetUpdate(SF, (R2(31, 31)) | (R1(31, 31)));
instr.SetUpdate(OF, bv(0));
instr.SetUpdate(rip, nxt_rip);
RECORD_INST("orl_r32_r32");
