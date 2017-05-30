#ifndef _FEASTOFFOO_COUNTBITS_H__
#define _FEASTOFFOO_COUNTBITS_H__

namespace feastoffoo {

  namespace countbits {
    namespace reference {
      extern unsigned int countbits(unsigned long long number);
    }

    namespace improvement1 {
      extern unsigned int countbits(unsigned int number);
      extern unsigned int countbits64(unsigned long long number);
    }

    namespace improvement2 {
      extern unsigned int countbits(unsigned int number);
      extern unsigned int countbits64(unsigned long long number);
    }

    namespace improvement3 {
      extern unsigned char countbits(unsigned char number);
      extern unsigned short countbits(unsigned short number);
      extern unsigned int countbits(unsigned int number);
      extern unsigned int countbits(unsigned long long number);
    }

    namespace improvement4 {
      extern int _countbits_4_finale;

      // add flexibility
      //
      // only need one countbits, not one for char, one for int, and one for long long
      //
      // the compiler can work out how long we have to add the bits together
      // before we can stop and just add using modulus
      template <typename _NUMBER, int _MASKSIZE, int _BITSLEFT>
      struct COUNTBITS_MASK_DETAIL {
        static const _NUMBER bits = ((1<<_MASKSIZE)-1) | ((COUNTBITS_MASK_DETAIL<_NUMBER, _MASKSIZE, (_BITSLEFT-(_MASKSIZE<<1))>::bits) << (_MASKSIZE<<1));
      };

      // the recursion counts down to zero
      template <typename _NUMBER, int _MASKSIZE>
      struct COUNTBITS_MASK_DETAIL<_NUMBER, _MASKSIZE, 0> {
        static const _NUMBER bits = ((1<<_MASKSIZE)-1);
      };

      // make it easier to use
      template <typename _NUMBER, int _MASKSIZE>
      struct COUNTBITS_MASK {
        static const _NUMBER mask = COUNTBITS_MASK_DETAIL<_NUMBER, _MASKSIZE, ((sizeof(_NUMBER)<<3)-(_MASKSIZE<<1))>::bits;
      };

      template <typename _NUMBER, int _MASKSIZE, bool _DONE>
      struct CountBits {
      };

      // does increasingly larger sums until the sum handles more bits than the input number can possibly have
      // this recursion counts up
      template <typename _NUMBER, int _MASKSIZE>
      struct CountBits<_NUMBER, _MASKSIZE, false> {
        static inline _NUMBER countbits(_NUMBER sum) {
          sum = ((sum >> _MASKSIZE) & COUNTBITS_MASK<_NUMBER, _MASKSIZE>::mask) + (sum & COUNTBITS_MASK<_NUMBER, _MASKSIZE>::mask);

          // recursion until number of bits in the number is less than what the mask can count
          // => as long as the number of bits is larger than what the mask can count, we need to keep
          // accumulating with larger masks
          return CountBits<_NUMBER, (_MASKSIZE<<1), ((sizeof(_NUMBER)<<3) < ((1<<(_MASKSIZE<<1))-1))>::countbits(sum);
        }
      };

      // recursion end
      template <typename _NUMBER, int _MASKSIZE>
      struct CountBits<_NUMBER, _MASKSIZE, true> {
        static inline _NUMBER countbits(_NUMBER sum) {
          return sum % (_countbits_4_finale = ((1<<_MASKSIZE)-1));
        }
      };

      template <typename _NUMBER>
      unsigned int countbits(_NUMBER number) {
        return (unsigned int) CountBits<_NUMBER, 1, false>::countbits(number);
      }
    }
  }

}

#endif
