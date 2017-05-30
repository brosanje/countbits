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

> [==========] Running 18 tests from 1 test case.
> [----------] Global test environment set-up.
> [----------] 18 tests from CountBits
> [ RUN      ] CountBits.Reference
> [       OK ] CountBits.Reference (0 ms)
> [ RUN      ] CountBits.ReferenceTimings
> [       OK ] CountBits.ReferenceTimings (89 ms)
> [ RUN      ] CountBits.Improvement1
> [       OK ] CountBits.Improvement1 (0 ms)
> [ RUN      ] CountBits.Improvement1VsReference32
> [       OK ] CountBits.Improvement1VsReference32 (44 ms)
> [ RUN      ] CountBits.Improvement1VsReference64
> [       OK ] CountBits.Improvement1VsReference64 (34 ms)
> [ RUN      ] CountBits.Improvement2
> [       OK ] CountBits.Improvement2 (0 ms)
> [ RUN      ] CountBits.Improvement2VsReference32
> [       OK ] CountBits.Improvement2VsReference32 (43 ms)
> [ RUN      ] CountBits.Improvement2VsReference64
> [       OK ] CountBits.Improvement2VsReference64 (33 ms)
> [ RUN      ] CountBits.Improvement3
> [       OK ] CountBits.Improvement3 (0 ms)
> [ RUN      ] CountBits.Improvement3VsReference8
> [       OK ] CountBits.Improvement3VsReference8 (35 ms)
> [ RUN      ] CountBits.Improvement3VsReference16
> [       OK ] CountBits.Improvement3VsReference16 (33 ms)
> [ RUN      ] CountBits.Improvement3VsReference32
> [       OK ] CountBits.Improvement3VsReference32 (43 ms)
> [ RUN      ] CountBits.Improvement3VsReference64
> [       OK ] CountBits.Improvement3VsReference64 (33 ms)
> [ RUN      ] CountBits.Improvement4
> [       OK ] CountBits.Improvement4 (0 ms)
> [ RUN      ] CountBits.Improvement4VsReference8
> [       OK ] CountBits.Improvement4VsReference8 (42 ms)
> [ RUN      ] CountBits.Improvement4VsReference16
> [       OK ] CountBits.Improvement4VsReference16 (63 ms)
> [ RUN      ] CountBits.Improvement4VsReference32
> [       OK ] CountBits.Improvement4VsReference32 (42 ms)
> [ RUN      ] CountBits.Improvement4VsReference64
> [       OK ] CountBits.Improvement4VsReference64 (46 ms)
> [----------] 18 tests from CountBits (581 ms total)
> 
> [----------] Global test environment tear-down
> [==========] 18 tests from 1 test case ran. (581 ms total)
> [  PASSED  ] 18 tests.
