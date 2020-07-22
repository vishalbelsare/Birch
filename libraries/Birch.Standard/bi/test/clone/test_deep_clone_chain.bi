/*
 * Test deep clone of an object, where clones are chained.
 */
program test_deep_clone_chain() {
  x:DeepCloneNode;
  x.a <- 1;
  
  /* clone, modify */
  auto y <- clone(x);
  y.a <- 2;
  
  /* clone the clone */
  auto z <- clone(y);
  
  /* erase the history of the chain */
  x <- z;
  y <- z;
  
  /* is z.b updated despite the missing history? */
  if z.a != 2 {
    exit(1);
  }
}

class DeepCloneNode {
  a:Integer;
}
