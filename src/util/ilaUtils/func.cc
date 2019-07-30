// helper functions for modeling x86


// FIXME: is the return type ExprRef?
ExprRef scanReverse(ExprRef in, unsigned int idx, unsigned int width) {
  if (idx == 0)
    return BvConst(0, width);
  return Ite( in(idx) == 1, BvConst(idx, width), scanReverse(in, idx-1, width);
}


// FIXME: is the return type ExprRef?
ExprRef scanForward(ExprRef in, unsigned int idx, unsigned int width) {
  if (idx == width - 1)
    return BvConst(width - 1, width);
  return Ite( in(idx) == 1, BvConst(idx, width), scanReverse(in, idx+1, width);
}
