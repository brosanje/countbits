# countbits
Challenge:

count ON bits in a fundamental type, char, short, int, long, long long.

feastoffoo::countbits::reference
  countbits uses a simple shift and increment if true algorithm.
  O(nbits)

feastoffoo::countbits::improvement1
  countbits uses mask -> shift -> add algorithm, which for each iteration
  is more complicated than the reference, but it's O(log nbits)

feastoffoo::countbits::improvement2
  same as above, but the bit masks are compiler generated using templates.

feastoffoo::countbits::improvement3
  uses the mask -> shift -> add algorithm until the masked number can
  hold a higher number than the number of bits in the fundamental type.
  once that point is reached, it sums the masked pieces in modulus.
  This is a constant number of steps, mostly independent on the size of
  the fundamental type.  2+1 steps for char and 3+1 steps for anything larger.
  O(c)

feastoffoo::countbits::improvement4
  a fully templated version of improvement3.
